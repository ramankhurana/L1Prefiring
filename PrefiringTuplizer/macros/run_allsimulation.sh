## adding +15 and +20 ns 
root -l -b <<EOF
 .L L1Prefiring.C++
L1Prefiring(2,"_plus15_","p15ns")
EOF


root -l -b <<EOF
 .L L1Prefiring.C++
L1Prefiring(4,"_plus15_","p15ns")
EOF


root -l -b <<EOF
 .L L1Prefiring.C++
L1Prefiring(6,"_plus15_","p15ns")
EOF


root -l -b <<EOF
 .L L1Prefiring.C++
L1Prefiring(8,"_plus15_","p15ns")
EOF


root -l -b <<EOF
 .L L1Prefiring.C++
L1Prefiring(2,"_plus20_","p20ns")
EOF


root -l -b <<EOF
 .L L1Prefiring.C++
L1Prefiring(4,"_plus20_","p20ns")
EOF


root -l -b <<EOF
 .L L1Prefiring.C++
L1Prefiring(6,"_plus20_","p20ns")
EOF

root -l -b <<EOF
 .L L1Prefiring.C++
L1Prefiring(8,"_plus20_","p20ns")
EOF


## remaining time shifts
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_minus8_","m8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_nosign0_","0ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_minus4_","m4ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_minus5_","m5ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_minus6_","m6ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_minus7_","m7ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_plus8_","p8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_plus12_","p12ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_minus4_","m4ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_minus8_","m8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_minus12_","m12ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_nosign0_","0ns")
####EOF
####
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_plus4_","p4ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(2,"_plus4_","p4ns")
####EOF
####
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_plus8_","p8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_plus12_","p12ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_minus4_","m4ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_minus8_","m8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_minus12_","m12ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_nosign0_","0ns")
####EOF
####
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_plus4_","p4ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_minus5_","m5ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_minus6_","m6ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_minus7_","m7ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_minus5_","m5ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_minus6_","m6ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_minus7_","m7ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_minus5_","m5ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_minus6_","m6ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(4,"_minus7_","m7ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(10,"_minus5_","m5ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(10,"_minus6_","m6ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(10,"_minus7_","m7ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_plus8_","p8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_plus12_","p12ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_minus4_","m4ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_minus8_","m8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_minus12_","m12ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(6,"_nosign0_","0ns")
####EOF
####
####
####
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_plus4_","p4ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_plus8_","p8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_plus12_","p12ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_minus4_","m4ns")
####EOF
####
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_minus8_","m8ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_minus12_","m12ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_nosign0_","0ns")
####EOF
####
####root -l -b <<EOF
#### .L L1Prefiring.C++
####L1Prefiring(8,"_minus8_","m8ns")
####EOF
