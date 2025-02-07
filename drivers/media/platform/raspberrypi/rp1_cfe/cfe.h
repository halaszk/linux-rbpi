/* SPDX-License-Identifier: GPL-2.0 */
/*
 * RP1 CFE driver.
 * Copyright (c) 2021 Raspberry Pi Ltd.
 *
 */
#ifndef _RP1_CFE_
#define _RP1_CFE_

#include <linux/types.h>
#include <linux/media-bus-format.h>
#include <linux/videodev2.h>

extern bool cfe_debug_irq;

enum cfe_remap_types {
	CFE_REMAP_16BIT,
	CFE_REMAP_COMPRESSED,
	CFE_NUM_REMAP,
};

#define CFE_FORMAT_FLAG_META_OUT	BIT(0)
#define CFE_FORMAT_FLAG_META_CAP	BIT(1)
#define CFE_FORMAT_FLAG_FE_OUT		BIT(2)

struct cfe_fmt {
	u32 fourcc;
	u32 code;
	u8 depth;
	u8 csi_dt;
	u32 remap[CFE_NUM_REMAP];
	u32 flags;
};

extern const struct v4l2_mbus_framefmt cfe_default_format;
extern const struct v4l2_mbus_framefmt cfe_default_meta_format;

const struct cfe_fmt *find_format_by_code(u32 code);

#endif
