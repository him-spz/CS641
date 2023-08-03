#! /usr/bin/expect -f

set timeout -1

spawn ssh student@65.0.124.36 

expect "*: "
send "Cryptonite\r"
expect "*: "
send "hesoyamo\r"
expect "*: "
send "4\r"
expect "*> "
send "read\r"

set fin_name "inputs1.txt"
set fin [open "$fin_name" r]
set in_data [read $fin]

set fout_name "rawoutputs1.txt"
set fout [open $fout_name "w"]
 
# Read line by line
foreach line $in_data {
  # puts "$line\r"
  
  expect "> "
  send "$line\r"

  expect "$line\r"  # discard command echo
  expect "Slowly, a new text starts appearing on the screen. It reads ..."
  expect "\n\t\t*\n"  # match and save the result
  puts -nonewline $fout "$expect_out(0,string)\n"

  expect "Press c to continue> "
  send "c\r"
}
close $fin
close $fout

set fin_name "inputs2.txt"
set fin [open "$fin_name" r]
set in_data [read $fin]

set fout_name "rawoutputs2.txt"
set fout [open $fout_name "w"]
 
# Read line by line
foreach line $in_data {
  # puts "$line\r"
  
  expect "> "
  send "$line\r"

  expect "$line\r"  # discard command echo
  expect "Slowly, a new text starts appearing on the screen. It reads ..."
  expect "\n\t\t*\n"  # match and save the result
  puts -nonewline $fout "$expect_out(0,string)\n"

  expect "Press c to continue> "
  send "c\r"
}
close $fin
close $fout

expect "*> "
send "back\r"
expect "*> "
send "exit\r"
