dataset=/ZeroBias1/Run2018D-v1/RAW run=324725
run=324725
searchquery="file dataset=$dataset run=$run"
echo $searchquery
dasgoclient --query="$searchquery" --limit=0  >& fileList.txt






