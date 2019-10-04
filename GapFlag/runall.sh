for which in gapflag_database/TIM_DATA_CONF_ID_1039.dat.txt gapflag_database/TIM_DATA_CONF_ID_1090.dat.txt gapflag_database/TIM_DATA_CONF_ID_1192.dat.txt gapflag_database/TIM_DATA_CONF_ID_1269.dat.txt gapflag_database/TIM_DATA_CONF_ID_287.dat.txt gapflag_database/TIM_DATA_CONF_ID_473.dat.txt gapflag_database/TIM_DATA_CONF_ID_651.dat.txt gapflag_database/TIM_DATA_CONF_ID_711.dat.txt gapflag_database/TIM_DATA_CONF_ID_756.dat.txt gapflag_database/TIM_DATA_CONF_ID_945.dat.txt; do 
    echo "running code for: " $which
    python gapFlagDataBaseAnalyzer.py -i $which
done


