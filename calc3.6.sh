#! /usr/bin/bash

#take user input
while true; do
	printf ">> "
	read a op b

AnsFile="ANS.txt"
HisFile="history.txt"

HIST(){
	tail -n 5 history.txt
}

if [[ ! -f "$HisFile" ]]; then
	touch history.txt
fi

if [[ -f "$AnsFile" ]]; then
	ans=$(<ANS.txt)
else
	ans=0
	touch ANS.txt
fi


# calculate operations
if [[ "$a" == "HIST" ]]; then
	HIST
	continue
elif [[ "$a" == "EXIT" ]]; then
	break
elif [[ "$a" == "ANS" && "$b" != "ANS" ]]; then
	case $op in
		+)res=`echo $ans + $b | bc`
		;;
		-)res=`echo $ans - $b | bc`
		;;
		/)
		if [ $b -eq 0 ]; then
			echo "MATH ERROR"
			continue
		else res=`echo "scale=2; $ans / $b" | bc`
		fi
		;;
		%)
		if [ $b -eq 0 ]; then
			echo "MATH ERROR"
			continue
		else res=`echo "scale=0; $ans / $b" | bc`
		fi
		;;
		*)
			if [[ "$op" == "*" ]]; then
			res=`echo "scale=2; $ans * $b" | bc`
			else
			echo "SYNTAX ERROR"
			continue
			fi
		;;
	esac
elif [[ "$b" == "ANS" && "$a" != "ANS" ]]; then
	case $op in
		+)res=`echo $a + $ans | bc`
		;;
		-)res=`echo $a - $ans | bc`
		;;
		/)
		if [ $ans -eq 0 ]; then
			echo "MATH ERROR"
			continue
		else res=`echo "scale=2; $a / $ans" | bc`
		fi
		;;
		%)
		if [ $ans -eq 0 ]; then
			echo "MATH ERROR"
			continue
		else res=`echo "scale=0; $a / $ans" | bc`
		fi
		;;
		*)
			if [[ "$op" == "*" ]]; then
			res=`echo "scale=2; $a * $ans" | bc`
			else
			echo "SYNTAX ERROR"
			continue
			fi
		;;
	esac
elif [[ "$a" == "ANS" && "$b" == "ANS" ]]; then
	case $op in
		+)res=`echo 2 * $ans | bc`
		;;
		-)res=0
		;;
		/)
		if [ $ans -eq 0 ]; then
			echo "MATH ERROR"
			continue
		else res=1
		fi
		;;
		%)
		if [ $ans -eq 0]; then
			echo "MATH ERROR"
			continue
		else res=1
		fi
		;;
		*)
			if [[ "$op" == "*" ]]; then
			res=`echo "scale=2; $ans * $ans" | bc`
			else
			echo "SYNTAX ERROR"
			continue
			fi
		;;
	esac
else
	case $op in
		+)res=`echo $a + $b | bc`
		;; 
		-)res=`echo $a - $b | bc`
		;;
		/)
		if [ $b -eq 0 ]; then
			echo "MATH ERROR"
			continue
		else res=`echo "scale=2; $a / $b" | bc`
		fi
		;;
		%)
		if [ $b -eq 0 ]; then
			echo "MATH ERROR"
			continue
		else res=`echo "scale=0; $a / $b" | bc`
		fi
		;;
		*)
			if [[ "$op" == "*" ]]; then
			res=`echo "scale=2; $a * $b" | bc`
			else
			echo "SYNTAX ERROR"
			continue
			fi
		;;
	esac
fi

echo "$res" > "$AnsFile"

echo  "$res"

echo "$a $op $b = $res" >> history.txt
done
