from pandas import  DataFrame, concat, Series, read_csv


def PrintTProfileData(csvfilename):
    print "-----------------------------------------------------------------------------------------"
    print "  CSV_file_name                             bin_number  mean     rms "
    df = read_csv(csvfilename)
    df_out=DataFrame(columns=['adc'])
    
    for adc in zip(df.adc):
        adcList =  adc[0].replace("[","").replace("]","").split(",")
        ## this will create a new dataframe which has only adc values as a list. 
        df_out= df_out.append({'adc':adcList}, ignore_index=True)
        
        
    for i in range(0,10):
        '''
        df_out['adc'] : this will give the set of 10 values for each row
        df_out['adc'].str[i] : this will give you ith column from the list. 
        df_out['adc'].str[i]).astype(float) : since we read from a text file, 
        it is a string, we convert it into a float. For each row this is extracted and 
        a array/vector/series is formed. so all the information for each row for the the ith element in the ADC list is present here. 
        ((df_out['adc'].str[i]).astype(float)).mean(): take  the mean of ith datasamples 
        '''
        print csvfilename, i, ((df_out['adc'].str[i]).astype(float)).mean(), ((df_out['adc'].str[i]).astype(float)).std()



PrintTProfileData("SelectedDataFrames_Histo_L1Prefiring_p17ns.csv")
PrintTProfileData("SelectedDataFrames_Histo_L1Prefiring_m17ns.csv")
PrintTProfileData("SelectedDataFrames_Histo_L1Prefiring_0ns.csv")
