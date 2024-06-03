import oneapi_test_utils as utils

if __name__=='__main__':

    print('[STEP 0]: Check enviroment and user configuration')
    # Check test_list configuration
    utils.assert_config()

    #1. Initialize Test
    print('[STEP 1]: Initialize test')
    test_list_df = utils.initTest()                             
    
    for i,row in test_list_df.iterrows():
        print("##########################")
        print("[INFO] Running test n. " + i.split('Test')[1] + "/" + str(test_list_df.shape[0]) )
        print("##########################")
        
        #2. Run samples
        print('[STEP 2]: Run ' +  str(row['sample_name']) + ' sample')
        utils.runSamples(row)

    #3. Save results in test_result.csv
    print('[STEP 3]: Save results')
    utils.savesResults()