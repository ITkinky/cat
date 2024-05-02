#!/bin/sh

specimen=./s21_grep
original=grep
patterns="ge 1"
log_file=log_grep.log
directory_with_tests=texts
flags="-e -i -v -l -h -c -n -f"

counter=0
texts=""
for file in "$directory_with_tests"/*; do
  if [[ -f "$file" ]]; then
    texts+=" $file"
  fi
done
#

touch log1.txt
touch log2.txt

echo "It's a test" > "$log_file"
for text in $texts; do
  for flag in $flags; do
    for pattern in $patterns; do
      ((counter++))
      $specimen $flag "$pattern" "$text" > log1.txt
      $original $flag "$pattern" "$text" > log2.txt
      diff=$(diff -s --suppress-common-lines -y log1.txt log2.txt)
      if ! [[ $diff == "Files log1.txt and log2.txt are identical" ]]; then
        echo "$flag $pattern $text" >> "$log_file"
      fi
    done
  done
done

echo $counter

rm log1.txt
rm log2.txt
