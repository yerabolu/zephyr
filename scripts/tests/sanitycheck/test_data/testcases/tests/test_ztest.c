	ztest_test_suite(test_api,
			 ztest_1cpu_unit_test(test_a) /* comment! */, 
/* comment */ztest_1cpu_unit_test(test_b), 
			 ztest_1cpu_unit_test(test_c),
			 ztest_unit_test(test_unit_a), ztest_unit_test(test_unit_b),
			 ztest_1cpu_unit_test(
				test_newline),
			 ztest_1cpu_unit_test(test_test_test_aa),
			 ztest_user_unit_test(test_user),
			 ztest_1cpu_unit_test(test_last));
	ztest_run_test_suite(test_api);

	ztest_test_suite(feature1,
                         ztest_unit_test(test_1a),
#ifdef CONFIG_WHATEVER 
						 ztest_unit_test(test_1b),
#endif
                         ztest_unit_test(test_1c)
                         );
		ztest_run_test_suite(feature1);