import oneapi_test_utils as utils

if __name__=='__main__':

    print("[STEP 0]: Check enviroment and user configuration")
    # Check test_list configuration
    utils.assert_config()

    #1. Initialize Test
    print("[STEP 1]: Initialize Test")
    #df_test_list = utils.initTest()

    #2. Build and compile the samples
    print("[STEP 2]: Build and compile")
    utils.buildAndCompile()                                 
    
    #for i,row in df_test_list.iterrows():
        #print(i)

        #3. Response variables measurement

    #4. Save results in test_result.csv
    print("[STEP 4]: Saves results ")
    utils.savesResults()