/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
 */

#ifndef _CAM_ACTUATOR_DEV_H_
#define _CAM_ACTUATOR_DEV_H_

#include <cam_sensor_io.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/module.h>
#include <linux/irqreturn.h>
#include <linux/iommu.h>
#include <linux/timer.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-subdev.h>
#include <cam_cci_dev.h>
#include <cam_sensor_cmn_header.h>
#include <cam_subdev.h>
#include "cam_sensor_util.h"
#include "cam_soc_util.h"
#include "cam_debug_util.h"

#define NUM_MASTERS 2
#define NUM_QUEUES 2

#define TRUE  1
#define FALSE 0

#define ACTUATOR_DRIVER_I2C "i2c_actuator"
#define CAMX_ACTUATOR_DEV_NAME "cam-actuator-driver"

#define MSM_ACTUATOR_MAX_VREGS (10)
#define ACTUATOR_MAX_POLL_COUNT 10

#ifdef CONFIG_USE_ROHM_BU64753
#define EEPROM_MAP_DATA_CNT 60
#define EEPROM_READ_START_INDEX 7856
#define EEPROM_READ_END_INDEX 7915
#define ROHM_ACTUATOR_II2_ADDR 0x76 //R:0xED, W:0xEC
#endif

enum cam_actuator_apply_state_t {
	ACT_APPLY_SETTINGS_NOW,
	ACT_APPLY_SETTINGS_LATER,
};

enum cam_actuator_state {
	CAM_ACTUATOR_INIT,
	CAM_ACTUATOR_ACQUIRE,
	CAM_ACTUATOR_CONFIG,
	CAM_ACTUATOR_START,
};

/**
 * struct cam_actuator_i2c_info_t - I2C info
 * @slave_addr      :   slave address
 * @i2c_freq_mode   :   i2c frequency mode
 */
struct cam_actuator_i2c_info_t {
	uint16_t slave_addr;
	uint8_t i2c_freq_mode;
};

struct cam_actuator_soc_private {
	struct cam_actuator_i2c_info_t i2c_info;
	struct cam_sensor_power_ctrl_t power_info;
};

/**
 * struct intf_params
 * @device_hdl: Device Handle
 * @session_hdl: Session Handle
 * @ops: KMD operations
 * @crm_cb: Callback API pointers
 */
struct intf_params {
	int32_t device_hdl;
	int32_t session_hdl;
	int32_t link_hdl;
	struct cam_req_mgr_kmd_ops ops;
	struct cam_req_mgr_crm_cb *crm_cb;
};

/**
 * struct cam_actuator_ctrl_t
 * @i2c_driver: I2C device info
 * @pdev: Platform device
 * @cci_i2c_master: I2C structure
 * @io_master_info: Information about the communication master
 * @actuator_mutex: Actuator mutex
 * @act_apply_state: Actuator settings aRegulator config
 * @id: Cell Index
 * @res_apply_state: Actuator settings apply state
 * @cam_act_state:   Actuator state
 * @gconf: GPIO config
 * @pinctrl_info: Pinctrl information
 * @v4l2_dev_str: V4L2 device structure
 * @i2c_data: I2C register settings structure
 * @act_info: Sensor query cap structure
 * @of_node: Node ptr
 * @device_name: Device name
 */
struct cam_actuator_ctrl_t {
	struct i2c_driver *i2c_driver;
	enum cci_i2c_master_t cci_i2c_master;
	struct camera_io_master io_master_info;
	struct cam_hw_soc_info soc_info;
	struct mutex actuator_mutex;
	uint32_t id;
	enum cam_actuator_apply_state_t setting_apply_state;
	enum cam_actuator_state cam_act_state;
	uint8_t cam_pinctrl_status;
	struct cam_subdev v4l2_dev_str;
	struct i2c_data_settings i2c_data;
	struct cam_actuator_query_cap act_info;
	struct intf_params bridge_intf;
	char device_name[20];
	struct platform_device *pdev;
};

#endif /* _CAM_ACTUATOR_DEV_H_ */
