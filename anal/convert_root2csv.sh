!/bin/bash

# root -b -q convert_root2csv.C\(\"../build2/AmBe_1e7_iso_01.root\",\"det\",\"output/AmBe_1e7_iso_01.csv\"\)

for i in {1..26}
do
    # echo $(printf "%02d" $i)
    root -b -q convert_root2csv.C\(\"../build/output/cathodeclub_$(printf "%02d" $i).root\",\"det\",\"cathodeclub/cathodeclub_$(printf "%02d" $i).csv\"\)
done

