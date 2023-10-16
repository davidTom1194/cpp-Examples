# run inputs and outputs for assignment to compare and time
# example usage: ./homemade-judge.sh | grep -e errors -e Accepted
# outputs all accepted values and valgrind errors
PA="pa13a";
echo "pa13a: Input & Expected Output";
time for i in {0..3};
do
echo;
echo "********** Homemade Judge **********************************************";
echo "********** Input for file $i **********";
cat $PA-input$i.txt | ./$PA;
echo "********** Expected Output for file $i **********";
cat $PA-output$i.txt;
echo "********** Color Difference for file $i **********";
cat $PA-input$i.txt | ./$PA > $PA-actual$i.txt;
colordiff $PA-actual$i.txt $PA-output$i.txt;
rm -rf $PA-actual*.txt
echo "********** Valgrind Script *********************************************";
echo;
valgrind cat $PA-input$i.txt | ./pa13a
done
