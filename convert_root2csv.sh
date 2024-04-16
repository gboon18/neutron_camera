!/bin/bash

for i in {1..26}
do
    root -b -q convert_root2csv.C\(\"../build/output/cathodeclub_$(printf "%02d" $i).root\",\"det\",\"cathodeclub/cathodeclub_$(printf "%02d" $i).csv\"\)
done

