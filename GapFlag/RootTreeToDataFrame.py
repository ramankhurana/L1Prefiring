import pandas 
from root_pandas import read_root
from sets import Set

df = read_root("EcalTPGParam.root", 'tpgmap', columns=["tcc", "tower", "stripInTower", "TCCch"])

fout = open("EcalTPGParam.csv","w")
fout.write("tcc tower stripInTower TCCch\n")
df_list = []
for tcc, tower, stripID, TCCch in zip(df.tcc, df.tower, df.stripInTower, df.TCCch) :
    listelement = (str(tcc)+" "+str(tower)+" "+str(stripID)+" "+str(TCCch))
    df_list.append(listelement)

print len(df_list)

df_set = Set(df_list)
print len(df_set)
for iele in df_set:
    fout.write(iele+"\n")

fout.close()
#df.to_csv("EcalTPGParam.csv")
