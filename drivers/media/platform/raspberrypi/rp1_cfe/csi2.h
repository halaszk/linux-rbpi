/* SPDX-License-Identifier: GPL-2.0 */
/*
 * RP1 CSI-2 driver.
 * Copyright (c) 2021 Raspberry Pi Ltd.
 *
 */
#ifndef _RP1_CSI2_
#define _RP1_CSI2_

#include <linux/debugfs.h>
#include <linux/io.h>
#include <linux/types.h>
#include <media/v4l2-device.h>
#include <media/v4l2-subdev.h>

#include "dphy.h"

#define CSI2_NUM_CHANNELS 4

enum csi2_mode {
	CSI2_MODE_NORMAL,
	CSI2_MODE_REMAP,
	CSI2_MODE_COMPRESSED,
	CSI2_MODE_FE_STREAMING
};

enum csi2_compression_mode {
	CSI2_COMPRESSION_DELTA = 1,
	CSI2_COMPRESSION_SIMPLE = 2,
	CSI2_COMPRESSION_COMBINED = 3,
};

struct csi2_cfg {
	u16 width;
	u16 height;
	u32 stride;
	u32 buffer_size;
};

struct csi2_device {
	/* Parent V4l2 device */
	struct v4l2_device *v4l2_dev;

	void __iomem *base;

	struct dphy_data dphy;

	enum v4l2_mbus_type bus_type;
	unsigned int bus_flags;
	u32 active_data_lanes;
	bool multipacket_line;
	unsigned int num_lines[CSI2_NUM_CHANNELS];

	struct media_pad pad[CSI2_NUM_CHANNELS * 2];
	struct v4l2_subdev sd;
};

void csi2_isr(struct csi2_device *csi2, bool *sof, bool *eof, bool *lci);
void csi2_set_buffer(struct csi2_device *csi2, unsigned int channel,
		     dma_addr_t dmaaddr, unsigned int stride,
		     unsigned int size);
void csi2_set_compression(struct csi2_device *csi2, unsigned int channel,
			  enum csi2_compression_mode mode, unsigned int shift,
			  unsigned int offset);
void csi2_start_channel(struct csi2_device *csi2, unsigned int channel,
			u16 dt, enum csi2_mode mode, bool auto_arm,
			bool pack_bytes, unsigned int width,
			unsigned int height);
void csi2_stop_channel(struct csi2_device *csi2, unsigned int channel);
void csi2_open_rx(struct csi2_device *csi2);
void csi2_close_rx(struct csi2_device *csi2);
int csi2_init(struct csi2_device *csi2, struct dentry *debugfs);
void csi2_uninit(struct csi2_device *csi2);

#endif
