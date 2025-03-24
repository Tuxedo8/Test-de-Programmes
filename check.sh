#!/bin/bash

Choix=(0 1 2 3 4 5 6 7 8 9) 
                  # 0 : CHAINE VIDE
                  # 1 : CHAINE CORRECTE LONGUEUR MINIMAL
                  # 2 : CHAINE CORRECTE IMBRICATION MINIMAL
                  # 3 : CHAINE INCORRECTE LONGUEUR MINIMAL
                  # 4 : CHAINE INCORRECTE IMBRICATION MINIMAL
                  # 5 : /BUG\ NE COMPTE PLUS LES OUVRANTES APRÈS UNE FERMANTE
                  # 6 : /BUG\ FERMANTES NON COMPTE
                  # 7 : /BUG\ OUVRANTES NON COMPTE
                  # 8 : /BUG\ PAS DE DIFFERENCE DE TYPE
                  # 9 : /BUG\ IMBRICATION SANS DIFFERENCE DE TYPE
                  
NBR=(20 50 100 300 500 1000 2000) # Valeurs minimal pour chaque chaine

iter=2

print_nbr_false_result(){
  
  echo "" > false_result.txt
  # 0 
  echo "Vide" >> false_result.txt
  echo "$(cat result.txt | grep -w "Vide" | grep "Mauvais" | wc -l)" >> false_result.txt
  # 1
  for i in "${NBR[@]}"; do
    echo "Correcte Longeur Min $i" >> false_result.txt
    echo "$(cat result.txt | grep -w "Correcte Longueur Min $i" | grep "Mauvais" | wc -l)" >> false_result.txt
  done
  # 2
  for i in "${NBR[@]}"; do
    echo "Correcte Imbrication Min $i" >> false_result.txt
    echo "$(cat result.txt | grep -w "Correcte Imbrication Min $i" | grep "Mauvais" | wc -l)" >> false_result.txt
  done
  # 3
  for i in "${NBR[@]}"; do
    echo "Incorrecte Longeur Min $i" >> false_result.txt
    echo "$(cat result.txt | grep -w "Incorrecte Longueur Min $i" | grep "Bon" | wc -l)" >> false_result.txt
  done
  # 4
  for i in "${NBR[@]}"; do
    echo "Incorrecte Imbrication Min $i" >> false_result.txt
    echo "$(cat result.txt | grep -w "Incorrecte Imbrication Min $i" | grep "Bon" | wc -l)" >> false_result.txt
  done
  # 5
  for i in "${NBR[@]}"; do
      echo "/BUG\ Ne compte plus les ouvrantes après une fermant longueur min $i" >> false_result.txt
      echo "$(grep -w "BUG Ne compte plus les ouvrantes après une fermant longueur min $i" result.txt | grep "Bon" | wc -l)" >> false_result.txt
  done
  # 6
  for i in "${NBR[@]}"; do
      echo "/BUG\ Fermante non compte longueur min $i" >> false_result.txt
      echo "$(grep -w "BUG Fermante non compte longueur min $i" result.txt | grep "Bon" | wc -l)" >> false_result.txt
  done
  # 7
  for i in "${NBR[@]}"; do
      echo "/BUG\ Ouvrante non compte longueur min $i" >> false_result.txt
      echo "$(grep -w "BUG Ouvrante non compte longueur min $i" result.txt | grep "Bon" | wc -l)" >> false_result.txt
  done
  # 8
  for i in "${NBR[@]}"; do
      echo "/BUG\ Pas de difference de type longueur min $i" >> false_result.txt
      echo "$(grep -w "BUG Pas de difference de type longueur min $i" result.txt | grep "Bon" | wc -l)" >> false_result.txt
  done
  # 9
  for i in "${NBR[@]}"; do
      echo "/BUG\ Imbrication sans difference de type min $i" >> false_result.txt
      echo "$(grep -w "BUG Imbrication sans difference de type min $i" result.txt | grep "Bon" | wc -l)" >> false_result.txt
  done

 
}

print_programs(){
    echo "" > result.txt
   for program in all_programs/program_*; do
      echo "----- $(basename "$program") ------" >> result.txt
      echo "Vide : $(head -$iter result_0_0.txt | tail -1 | cut -d " " -f 3-)" >> result.txt
      
      for i in "${Choix[@]}"; do
        for j in "${NBR[@]}"; do
          
          if [ "$i" -eq 0 ];
          then
            continue
          else
            if [ "$i" -eq 1 ];
            then
              echo "Correcte Longueur Min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt
            elif [ "$i" -eq 2 ];
            then
              echo "Correcte Imbrication Min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt
            elif [ "$i" -eq 3 ];
            then
              echo "Incorrecte Longueur Min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt
            elif [ "$i" -eq 4 ];
            then
              echo "Incorrecte Imbrication Min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt       
            
            elif [ "$i" -eq 5 ];
            then
              echo "BUG Ne compte plus les ouvrantes après une fermant longueur min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt

            elif [ "$i" -eq 6 ];
            then
              echo "BUG Fermante non compte longueur min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt

            elif [ "$i" -eq 7 ];
            then
              echo "BUG Ouvrante non compte longueur min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt            
            elif [ "$i" -eq 8 ];
            then
              echo "BUG Pas de difference de type longueur min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt             

            else
              echo "BUG Imbrication sans difference de type min $j : $(head -$iter result_${i}_${j}.txt | tail -1 | cut -d " " -f 3-)" >> result.txt   
            fi
          fi
        done
      done
      ((iter++)) 
      echo "" >> result.txt
   done
}

run_programs(){
  if [[ "$1" -eq 0 && "$2" -eq 0 ]];
  then
    for program in all_programs/program_*; do
          echo "$(basename "$program") : "$(all_programs/./"$(basename "$program")" < output.txt)"" >> result_0_0.txt
    done
  else
    for program in all_programs/program_*; do
          echo "$(basename "$program") : "$(all_programs/./"$(basename "$program")" < output.txt)"" >> result_${1}_${2}.txt
    done
  fi
}

echo -e "DEBUT DES TESTS (peut prendre quelque minutes)"
echo -e "Envie d'un café ?"
echo -e "Parce que ça va être long..."

for i in "${Choix[@]}"; do
  for j in "${NBR[@]}"; do
    ./test1 $i $j
    if [ "$i" -eq 1 ];
    then
      echo -e "----- CHAINE CORRECTE LONGUEUR MINIMAL "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_correcte_longueur_min_${j}

    elif [ "$i" -eq 2 ];
    then
      echo -e "----- CHAINE CORRECTE IMBRICATION MINIMAL "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_correcte_imbrication_min_${j}

    elif [ "$i" -eq 3 ];
    then
      echo -e "----- CHAINE INCORRECTE LONGUEUR MINIMAL "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_incorrecte_longueur_min_${j}
    elif [ "$i" -eq 4 ];
    then
      echo -e "----- CHAINE INCORRECTE IMBRICATION MINIMAL "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_incorrecte_imbrication_min_${j}
    elif [ "$i" -eq 5 ];
    then
      echo -e "----- /BUG\ NE COMPTE PLUS LES OUVRANTES APRÈS UNE FERMANT LONGUEUR MIN "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_bug_ouvrante_pas_compte_apres_fermante_lg_min_${j}
 elif [ "$i" -eq 6 ];
    then
      echo -e "----- /BUG\ FERMANTE NON COMPTE LONGUEUR MIN "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_bug_fermante_non_compte_lg_min_${j}
 elif [ "$i" -eq 7 ];
    then
      echo -e "----- /BUG\ OUVRANTE NON COMPTE LONGUEUR MIN "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_bug_ouvrante_non_compte_lg_min_${j}
 elif [ "$i" -eq 8 ];
    then
      echo -e "----- /BUG\ PAS DE DIFFERENCE DE TYPE LONGUEUR MIN "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_bug_pas_difference_type_lg_min_${j}
 elif [ "$i" -eq 9 ];
    then
      echo -e "----- /BUG\ IMBRICATION SANS DIFFERENCE DE TYPE MIN "$j" -----" > result_${i}_${j}.txt
      cat output.txt > chaine_bug_imbrication_sans_difference_de_type_min_${j}

    else
      if [ -e "result_0_0.txt" ];
      then
        continue
      else
        ./test1 0 0
        echo -e "----- CHAINE VIDE -----" > result_0_0.txt
        cat output.txt > chaine_vide
        run_programs "0" "0"
        continue
      fi
    fi
    run_programs "$i" "$j"

  done
done

clear
echo -e "FIN des tests (ENFIN !!)"
echo -e "Archivage des resultats par programmes dans $(pwd)/result.txt"
echo -e "Allez, c'est repartie pour un tour..."
print_programs

clear
echo -e "Fin de l'archivage dans $(pwd)/result.txt"
echo -e "Archivage du nombre de programmes faux par chaine dans $(pwd)/false_result.txt"
print_nbr_false_result


echo -e "Archivage des chaines utiliser dans $(pwd)/all_chaines/"
if test -d "$(pwd)/all_chaines/"; then
  echo -e "Le dossier all_chaines/ existe déja. Remplacement du contenu"
  rm all_chaines/*
else
  echo -e "Création du dossier all_chaines/"
  mkdir all_chaines
fi
mv chaine_* $(pwd)/all_chaines/

echo -e "Suppression des fichier temporaire (Il y en avait pas mal)"
rm result_*
echo -e "TERMINÉ"
echo -e "J'espère que le PC n'a pas trop soufflé HA HA"


