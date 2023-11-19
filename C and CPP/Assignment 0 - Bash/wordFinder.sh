#!/bin/bash

param_array=($@)
array_len=$#

# First part : Verify the input : ${#param_array[@]}
num_param_check_func() {

	if [ $array_len -lt 3 ] ; then
		echo "Number of parameters received : $array_len" >&2 
		echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>" ; exit 0	
	fi
	
} # end of the func.

num_param_check_func # First check.
b_last=${param_array[-2]}
b_last_len=${#b_last}
last=${param_array[-1]}
#echo $b_last ; echo $last ; echo $b_last_len


param_check_func() {
	#if ! ([[ $b_last =~ ^[[:alnum:]]+$ ]] && [ $b_last_len -eq 1 ] &&  [ $last > 0 ])  ; then #-lt
	if ! ( [[ $b_last =~ ^[[:alnum:]]+$ ]] && [ $b_last_len -eq 1 ] ) && ( (! [[ $last =~ ^[0-9]+$ ]]) || [ $last -lt 0 ] )   ; then
		echo "Only one char needed : $b_last" >&2
		echo "Not a positive number : $last" >&2
		echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>" ; exit 
	elif ! ([[ $b_last =~ ^[[:alnum:]]+$ ]] && [ $b_last_len -eq 1 ]) ; then
		echo "Only one char needed : $b_last" >&2
		echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>" ; exit
	#elif  ; then
	elif ( (! [[ $last =~ ^[0-9]+$ ]]) || [ $last -lt 0 ] ) ; then
		echo "Not a positive number : $last" >&2
		echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>" ; exit 
	fi
	
} # end of the func.

param_check_func # Second check.
#echo "Finished first part successfully !"
# Second part :	
file_check_func() {

	local counter=0;
	for(( i=0; i<array_len -2; i++ ));
	do
		if [ ! -f ${param_array[i]} ] ; then
			counter=$(($counter +1))
			wf_name="$(basename ${param_array[i]})"
			echo "File does not exist : $wf_name" >&2 # check if \n necessary !
			#echo $counter
			
		 fi
	done
	if [ $counter -ne 0 ] ; then
		echo "Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>" ; exit
	fi

} # end of the func.
file_check_func # Third check.
if [[ $b_last == [A-Z] ]]; then
	b_last=$(echo $b_last | tr '[:upper:]' '[:lower:]')
fi

# third part : iterate trow all of the files (in case there is 
# more than one file)
find_indx() { # The function finds the index of the element in word_arr.

   index=-1
   word_arr_len=${#word_arr[@]}
   for(( k=0; k<word_arr_len; k++));
   do
      if [[ "${word_arr[k]}" == "${line_arr[j]}" ]] ; then
         index=$k
         break
        fi
   done
   
}

count_func() {

	local counter=0
	word=$b_last
	#word=${param_array[-2]}
	index_arr=() ; word_arr=() ; count_arr=() # declaring arrays for the final resuls.
	#echo "Test : the word we want to lean on is : $word" #for debbugging !
	
	for(( i=0; i<array_len -2; i++));
	do
                tr '[A-Z]' '[a-z]' <${param_array[i]} >temp_file.txt
		declare -a line_arr=() # declaring temp arr for the file lines.   
		line_arr=( $( grep -o -E '\b'$b_last'\w{'$(( ${param_array[-1]} - 1))',}\b' temp_file.txt |sort ))
		#line_arr=( $( grep -o -E '\b'${param_array[-2]}'\w{'$(( ${param_array[-1]} - 1))',}\b' temp_file.txt |sort ))
		arr_len=${#line_arr[@]}
		for(( j=0; j<arr_len; j++));
      		do
      		
			if [[ ${line_arr[j]} == $word* ]] && [ ${#line_arr[j]} -ge $last ] ; then
					
				if ! echo ${word_arr[@]} | grep -q -w "${line_arr[j]}" ; then
						
					word_arr[${#word_arr[@]}]=${line_arr[j]} # add the value to the word_arr
					count_arr[${#count_arr[@]}]=1
				else
					find_indx
					count_arr[index]=$((${count_arr[index]} +1))
						
				fi # terminate the inned if condition.
				#else
					#echo "BREAKK"
					#break
			fi # terminate the outter if condition.
		done
		line_arr=()
		t_line_arr=()         
		rm temp_file.txt
	done # terminate the first for loop. 
}

count_func
#echo " the words are : ${word_arr[@]}"
#echo "the count is : ${count_arr[@]}"
#echo "Number of elements in the count array -> ${#count_arr[@]}"
wa_len=${#word_arr[@]}
# Forth part : Sort the arrays !

swap_func() {

	tmp1=${count_arr[$j]} # count_arr swaps !
	count_arr[$j]=${count_arr[$j+1]}
	count_arr[$j+1]=$tmp1
	tmp2=${word_arr[$j]} # word_arr swaps !
	word_arr[$j]=${word_arr[$j+1]}
	word_arr[$j+1]=$tmp2

}
bubble_sort_func() {

	flag=1
	for(( i=0; i<wa_len-1 && flag==1; i++)); do
		flag=0
		for(( j=0; j<wa_len-i-1; j++)); do
			if [ ${count_arr[$j]} -gt ${count_arr[$j+1]} ]; then
				swap_func
				flag=1
			elif [ ${count_arr[$j]} -eq ${count_arr[$j+1]} ]; then
				if [[ ${word_arr[$j]} > ${word_arr[$j+1]} ]]; then
					swap_func
					flag=1
				fi
			else
				continue
			fi
		done
	done
}

bubble_sort_func
#echo " the words are : ${word_arr[@]}"
#echo "the count is : ${count_arr[@]}"
for(( i=0; i<wa_len; i++ )) ; do
	echo "${count_arr[i]} ${word_arr[i]}"
done

