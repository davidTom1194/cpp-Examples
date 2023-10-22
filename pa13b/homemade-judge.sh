# run inputs and outputs for assignment to compare and time
# example usage: ./homemade-judge.sh | grep -e errors -e Accepted
# outputs all accepted values and valgrind errors
PA="pa13b";
PJUDGE="Pjudge";
echo "pa12: Input & Expected Output";
time for i in {0..2};
do
echo;
echo "********** Homemade Judge **********************************************";
echo "********** Input for file $i **********";
cat $PJUDGE/$PA-input$i.txt | ./$PA;
echo "********** Expected Output for file $i **********";
cat $PJUDGE/$PA-output$i.txt;
echo "********** Color Difference for file $i **********";
cat $PJUDGE/$PA-input$i.txt | ./$PA > $PA-actual$i.txt;
colordiff $PA-actual$i.txt $PJUDGE/$PA-output$i.txt;
rm -rf $PA-actual*.txt
echo "********** CSN Judge Script ********************************************";
echo;
judge -p $PA -i $PJUDGE/$PA-input$i.txt -o $PJUDGE/$PA-output$i.txt -v
echo "********** Valgrind Script *********************************************";
echo;
valgrind cat $PJUDGE/$PA-input$i.txt | ./pa13a
done
