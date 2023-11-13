# run inputs and outputs for assignment to compare and time
# example usage: ./homemade-judge.sh | grep -e errors -e Accepted
# outputs all accepted values and valgrind errors
PA="pa14";
PJUDGE="Pjudge";
echo "pa: Input & Expected Output";
time for i in {0..2};
do
echo "********** CSN Judge Script ********************************************";
echo;
judge -p $PA -i $PJUDGE/$PA-input$i.txt -o $PJUDGE/$PA-output$i.txt -v -t 90
done
