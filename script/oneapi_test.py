import oneapi_test_utils as utils

if __name__=='__main__':

    print("[STEP 0]: Check enviroment and user configuration")
    # Check test_list configuration
    utils.assert_config()

    #1. Initialize Test
    print("[STEP 1]: Initialize Test")
    df_test_list = utils.initTest()

    #2. Build and compile the samples
    print("[STEP 2]: Build and compile samples")
    utils.buildCompileSamples()                                 
    
    for i,row in df_test_list.iterrows():
        print("##########################")
        print("[INFO] Running test n. " + i.split('Test')[1] + "/" + str(df_test_list.shape[0]) )
        print("##########################")
        
        #print(row['array_size'])

        #3. Run samples
        print("[STEP 3]: Run samples")
        utils.runSamples(row)

    #4. Save results in test_result.csv
    print("[STEP 4]: Saves results")
    utils.savesResults()