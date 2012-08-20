/*
 * HID driver for primax and similar keyboards with in-band modifiers
 *
 * Copyright 2011 Google Inc. All Rights Reserved
 *
 * Author:
 *	Terry Lambert <tlambert@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
Edited by aleksandr.rakov@gmail.com 20.08.2012
Now is Lenovo Ideacentre A320 keyboard driver
*/

#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>

static int px_raw_event(struct hid_device *hid, struct hid_report *report,
	 u8 *data, int size)
{
	int idx = size;

	switch (report->id) {
	case 1:		/* keyboard input */
		/*
		 * Convert in-band modifier key values into out of band
		 * modifier bits and pull the key strokes from the report.
		 * first byte olways [01]
		 * Thus a report data set which looked like:
		 *
		 * [01][00][00][E0][30][00][00][00][00]
		 * (no modifier bits + "Left Shift" key + "1" key)
		 *
		 * Would be converted to:
		 *
		 * [01][01][00][00][30][00][00][00][00]
		 * (Left Shift modifier bit + "1" key)
		 *
		 * As long as it's in the size range, the upper level
		 * drivers don't particularly care if there are in-band
		 * 0-valued keys, so they don't stop parsing.
		 */
		while (--idx > 1) {
			if (data[idx] < 0xE0 || data[idx] > 0xE7)
				continue;
			data[1] |= (1 << (data[idx] - 0xE0));
			data[idx] = 0;
		}
		hid_report_raw_event(hid, HID_INPUT_REPORT, data, size, 0);
		return 1;

	default:	/* unknown report */
		/* Unknown report type; pass upstream */
		break;
	}
	return 0;
}

static int px_probe(struct hid_device *hid, const struct hid_device_id *id)
{
	int ret;

	ret = hid_parse(hid);
	if (ret) {
		hid_err(hid, "parse failed\n");
		goto fail;
	}

	ret = hid_hw_start(hid, HID_CONNECT_DEFAULT);
	if (ret)
		hid_err(hid, "hw start failed\n");

fail:
	return ret;
}

static void px_remove(struct hid_device *hid)
{
	hid_hw_stop(hid);
}

static const struct hid_device_id px_devices[] = {
	{ HID_USB_DEVICE(0x0a5c, 0x4502) },
	{ }
};
MODULE_DEVICE_TABLE(hid, px_devices);

static struct hid_driver px_driver = {
	.name = "a320",
	.id_table = px_devices,
	.raw_event = px_raw_event,
	.probe = px_probe,
	.remove = px_remove,
};

static int __init px_init(void)
{
	return hid_register_driver(&px_driver);
}

static void __exit px_exit(void)
{
	hid_unregister_driver(&px_driver);
}

module_init(px_init);
module_exit(px_exit);
MODULE_AUTHOR("Terry Lambert <tlambert@google.com>");
MODULE_LICENSE("GPL");
