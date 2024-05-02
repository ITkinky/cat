#!/bin/sh

specimen=./s21_cat
original=cat
log_file=log_cat.log
directory_with_tests=texts
flags="-b -e -n -s -t"

counter=0
texts=""
for file in "$directory_with_tests"/*; do
  if [[ -f "$file" ]]; then
    texts+=" $file"
  fi
done


touch log1.txt
touch log2.txt

echo "It's a test" > "$log_file"

for text in $texts; do
      ((counter++))
      $specimen "$text" > log1.txt
      $original "$text" > log2.txt
      diff=$(diff -s --suppress-common-lines -y log1.txt log2.txt)
      if ! [[ $diff == "Files log1.txt and log2.txt are identical" ]]; then
        echo "$flag $pattern $text" >> "$log_file"
      fi
done

for text in $texts; do
  for flag in $flags; do
      ((counter++))
      $specimen $flag "$text" > log1.txt
      $original $flag "$text" > log2.txt
      diff=$(diff -s --suppress-common-lines -y log1.txt log2.txt)
      if ! [[ $diff == "Files log1.txt and log2.txt are identical" ]]; then
        echo "$flag $pattern $text" >> "$log_file"
      fi
  done
done

echo $counter

rm log1.txt
rm log2.txt
