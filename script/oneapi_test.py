import oneapi_test_utils as utils

if __name__=='__main__':

    print("[STEP 0]: Check enviroment and user configuration")
    # Check test_list configuration
    utils.assert_config()

    #1. Initialize Test
    print("[STEP 1]: Initialize Test")
    #df_test_list = utils.initTest()

    #2. Build and compile the program
    print("[STEP 2]: Build and compile: ")
    utils.buildAndCompile()                                 
    
    #for i,row in df_test_list.iterrows():
        #print(i)

        #3. Response variables measurement

    #4. Save response variabiles in test_result.csv