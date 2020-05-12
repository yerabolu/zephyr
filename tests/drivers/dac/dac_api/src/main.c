/*
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @addtogroup t_driver_dac
 * @{
 * @defgroup t_dac_basic test_dac_basic_operations
 * @}
 */

#include <zephyr.h>
#include <ztest.h>

extern void test_dac_write_value(void);
extern struct device *get_dac_device(void);

void test_main(void)
{
	k_object_access_grant(get_dac_device(), k_current_get());

	ztest_test_suite(dac_basic_test,
			 ztest_user_unit_test(test_dac_write_value));
	ztest_run_test_suite(dac_basic_test);
}
