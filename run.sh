for i in $(seq 1 5)
do
  ./bin/lllw ./input/iccad2015_input.case$i ./output/iccad2015_output.case$i
done
