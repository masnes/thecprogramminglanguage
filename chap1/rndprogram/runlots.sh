for j in {1..10}
do 
  for i in {1..1000}
  do
    cat randomwordpicker.c | ./a.out >> output.txt
  done
  echo j
done
