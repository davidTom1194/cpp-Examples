# run inputs and outputs for assignment to compare and time
# example usage: ./homemade-judge.sh | grep -e errors -e Accepted
# outputs all accepted values and valgrind errors
PA="pa18";
PJUDGE="Pjudge";
echo "PA: Input & Expected Output";
time for i in {0..3};
do
echo;
echo "********** Homemade Judge **********************************************";
# echo "********** Input for file $i **********";
# cat $PJUDGE/$PA-input$i.txt | ./$PA;
# echo "********** Expected Output for file $i **********";
# cat $PJUDGE/$PA-output$i.txt;
echo "********** Color Difference for file $i **********";
cat $PJUDGE/$PA-input$i.txt | ./$PA > $PA-actual$i.txt;
colordiff $PA-actual$i.txt $PJUDGE/$PA-output$i.txt;
rm -rf $PA-actual*.txt
echo "********** CSN Judge Script ********************************************";
echo;
judge -p $PA -i $PJUDGE/$PA-input$i.txt -o $PJUDGE/$PA-output$i.txt -v -t 15
#echo "********** Valgrind Script *********************************************";
#echo;
#valgrind cat $PJUDGE/$PA-input$i.txt | ./pa18
done
