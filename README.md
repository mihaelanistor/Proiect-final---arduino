# Proiect-final arduino

Descriere:
									
		Robotel care raspunde la comenzi trimise de pe telefon prin bluetooth
Implementare:

	  In prima secventa de cod din loop, este apelata functia care primeste date de la bluetooth(BT).
  	Pentru a retine ce comenzi au fost trimise prin BT am folosit un vector cu valori de 0 si 1 (0 pe pozitia i inseamna
		ca comanda i nu a fost selectata, 1 - in caz contrar).
  	Apoi iteram prin vectorul de comenzi si pentru fiecare valoare de 1 apelam functia respectiva comenzii.
    	Comenzi posibile:
      		- mergi in fata
      		- stai
      		- mergi in stanga
      		- mergi in dreapta
      		- mergi cu spatele
					- mod line follower
      		- mod ocoleste obiecte
      		- canta

  	Pentru primele 5 comenzi (legate de miscare) se apeleaza aceeasi functie ("go()"), dar cu parametri diferiti
		(parametrii sunt vitezele pentru fiecare motor).
  	Functia pt linefollower citeste valorile de la senzorii IR si le salveaza intr-un vector de 6 elemente (6 senzori 
		folositi), iar atunci cand linia neagra nu este centrata, una din roti este oprita pana cand robotelul e recentrat pe linie.
  	Functia pentru ocolit obiecte misca servo motorul la 4 unghiuri diferite si la fiecare unghi se citeste o valoare de la 
		senzorul cu ultrasunete (care e lipit de servo motor). Daca una dintre cele 4 distante calculate pana la primul obiect
		din fata robotelului este mai mica de 5 cm, atunci robotelul da cu spatele pana cand distanta devine de 10 cm, apoi timp
		de o secunda se roteste(apx. 90 de grade) si pleaca mai departe. Functie trebuie imbunatatita si testata.
  	Pentru a canta, am folosit funtia tone(), care seteaza o anumita frecventa la un pin dat (pinul la care este conectat 
		speakerul).
  
