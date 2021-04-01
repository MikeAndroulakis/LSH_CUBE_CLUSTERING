Ονομα					ΑΜ
Άννα Πετρίδου			   1115201600135
Μιχάλης Ανδρουλάκης		   1115201600004



Για το LSH και το Cube χρησιμοποιουνται τα εξης αρχεια
(καποια και στο Clustering):
Functions_for_both_algorithms/Calculate_Distances.cpp    ,   Functions_for_both_algorithms/Calculate_Distances.h   , Functions_for_both_algorithms/h_Function.cpp ,  
Functions_for_both_algorithms/h_Function.h   ,   Functions_for_both_algorithms/Modulos.cpp ,   Functions_for_both_algorithms/Modulos.h    , 
Functions_for_both_algorithms/Quicksort.cpp  ,   Functions_for_both_algorithms/Quicksort.h ,   Functions_for_both_algorithms/Reading.cpp  ,  
Functions_for_both_algorithms/Reading.h      ,   Functions_for_both_algorithms/Writing.cpp ,   Functions_for_both_algorithms/Writing.h    .

 
LSH

Για το Lsh χρησιμοποιουνται τα εξης αρχεια:
Lsh/Hash.cpp , Lsh/Hash.h , Lsh/LSH.cpp , Lsh/LSH.h , Lsh/mainLSH.cpp , Lsh/Makefile

Το πρόγραμμα διαβάζει τη γραμμή εντολών.Πιθανες μεταβλητες που μπορει να διαβασει ειναι:Το αρχειο train,Το αρχειο των queries,το αρχειο output που γραφονται τα
αποτελεσματα,τον αριθμο k που ειναι ο αριθμος των συναρτησεων h,o αριθμος L που ειναι ο αριθμος των συναρτησεων g,ο αριθμος Ν που ειναι ο αριθμος των κοντινοτερων
γειτονων που θα ψαξει και ο αριθμος R που ειναι η ακτινα.Αν δε δωθει καποιο απο τους αριθμους τοτε επιλεγεται oι default τιμες που ειναι:
k=4,L=5,N=1,R=10000.Aν δε δωσουμε το train,query ή output αρχειο απτη γραμμη το προγραμμα τα ζηταει επειτα.
Αρχιζουμε με το διαβασμα του αρχειου train,και επειτα αρχικοποιουμε το W ως τη μεση αποσταση απο τον πλησιεστερο γειτονα για ενα δειγμα του dataset.
Στη συνεχεια υπολογιζουμε τα modulos του m,δηλαδη τα (m^x) mod M  , και τα αποθηκευουμε σε εναν vector καθως αυτες οι τιμες παραμενουν ιδιες για ολες
τις εικονες.Επειτα κανουμε το hash των εικονων αρχειου για καθε g σε μια δομη που λεγεται Hash.Πιο συγκεκριμενα για καθε g υπολογιζουμε τις k h συναρτησεις
και για καθε h εχουμε ενα vector οπου αποθηκευουμε τους d(οπου d η διασταση των εικονων) τυχαιους αριθμους s απο 0 εως W.Υπολογιζουμε για καθε εικονα τις k 
τιμες που προκυπτουν απο το αθροισμα των διαφανειων της σελιδας 20 και επειτα κανουμε concat για να βρουμε τη τιμη της g ως αποτελεσμα των k τιμων h.
Επειτα χασαρεται η καθε εικονα στο μπακετ που προκυπτει απο το αποτελεσμα g_value%(n/BUCKET_PARAMETER) καθως ο αριθμος των μπακετς που εχουμε 
σε καθε table ειναι n/BUCKET_PARAMETER.
Στη συνεχεια κανουμε την ιδια διαδικασια για τα queries μονο που τωρα αντι να αποθηκευτει ο αριθμος της εικονας του query απλα κανει Load τις εικονες του
μπακετ που εγινε hash.Ελεγχει τις αποστασεις ολων των εικονων με διαδικασια η οποια γινεται για καθε g και γραφει στο αρχειο τις καλυτερες καθως και τις εικονες 
που βρισκονται εντος της ακτινας R.Εχουμε και καταλληλες μεταβλητες για τον υπολογισμο των χρονων.
Επειτα βρισκει τις πραγματικα κοντινοτερες εικονες απο ολο το dataset ψαχνοντας τες μια-μια.Οταν γινει ολο αυτο,το προγραμμα ρωταει αν θελετε να
ξανατρεξετε την αναζητηση για αλλο αρχειο αναζητησης και αν απαντησετε ναι σας ζηταει τα καινουρια query και output αρχεια και επαναλμβανει την διαδικασια
των queries.

Στο αρχειο mainLSH μπορουμε να αλλαξουμε τις 2 define μεταβλητες που ειναι το MULTIPLIER και το BUCKET_PARAMETER.Το πρωτο επηρεαζει τη τιμη του W και αρα την 
αναλογια χρονου/ορθοτητας και η αλλη τον αριθμο των μπακετς που θα εχει καθε table της καθε g.

Οδηγιες Μεταγλωτισης:Μπορειτε να επιλεξετε οποιαδηποτε μεταβλητη θελετε να αλλαξετε αν δεν σας ικανοποιουν οι default τιμες,και μπορειτε να επιλεξετε να
δωσετε οποιοδηποτε απο το ή τα αρχειο ή αρχεια επιθυμητε αλλιως τα υπολοιπα θα ζητηθουν απο το προγραμμα στη συνεχεια.Ενα πιθανο τρεξιμο του προγραμματος θα ηταν
για παραδειγμα το:
./lsh -d /home/user/Desktop/project1/train-images.idx3-ubyte -q /home/user/Desktop/project1/t10k-images.idx3-ubyte  -N 20 -R 10000 -o /home/user/Desktop/project1/outputLSH.txt -L 6 -k 5

CUBE

Για το Cube χρησιμοποιουνται τα εξης αρχεια:
Cube/Cube.cpp , Cube/Cube.h , Cube/Cube_Struct.cpp , Cube/Cube_Struct.h , Cube/f_Function_Cube.cpp , Cube/f_Function_Cube.h  , Cube/h_Function_Cube.cpp ,
Cube/h_Function_Cube.h , Cube/mainCUBE.cpp , Cube/Makefile .

Το πρόγραμμα διαβάζει τη γραμμή εντολών.Πιθανες μεταβλητες που μπορει να διαβασει ειναι:Το αρχειο train,Το αρχειο των queries,το αρχειο output που γραφονται τα
αποτελεσματα,τον αριθμο k που επηρεαζει τα m και Μ,ο αριθμος Ν που ειναι ο αριθμος των κοντινοτερων
γειτονων που θα ψαξει, ο αριθμος probes που ειναι ο αριθμος των γειτονικων corners που θα ψαξει, ο αριθμος Μ που ειναι ο αριθμος των max γειτονων που θα ελεγξει 
και ο αριθμος R που ειναι η ακτινα.Αν δε δωθει καποιο απο τους αριθμους τοτε επιλεγεται oι default τιμες που ειναι:
k=14,N=1,Μ=10,probes=2,R=10000.Aν δε δωσουμε το train,query ή output αρχειο απτη γραμμη το προγραμμα τα ζηταει επειτα.
Αρχιζουμε το διαβασμα του αρχειου train, και επειτα αρχικοποιουμε το W ως τη μεση αποσταση απο τον πλησιεστερο γειτονα για ενα δειγμα του dataset.
Επειτα βρισκουμε τον αριθμο των συναρτησεων f που ειναι ο λογαριθμος του αριθμου των εικονων του training μειον 1.Υπολογιζουμε των αριθμο των corners του cube 
που ειναι ο αριθμος 2^d.Στη συνεχεια βρισκουμε τις τυχαιες τιμες s για τις d h και μεσω unordered map και uniform_distribution κανουμε hash ,καθε τιμη 
της h για καθε f, στο 0 ή το 1 και απο τις d 0-1 τιμες που θα προκυψουν βρισκουμε σε ποιο corner θα αποθηκευσουμε την εικονα.Στη συνεχεια κανουμε την ιδια
διαδικασια για τα queries ομως αντι να αποθηκευτουν στο συγκεκριμενο corner κανουν απλα Load τις εικονες αυτου.Για καθε query θα ελεγξουμε το πολυ Μ εικονες
και το πολυ probes corners προχωροντας στην επομενη εικονα επειτα.Τα αποτελεσματα γραφονται στο αρχειο εξοδου.

Στο αρχειο  mainCUBE μπορουμε να αλλαξουμε τις 1 define μεταβλητη που ειναι το MULTIPLIER ,το οποιο επηρεαζει τη τιμη του W και αρα την 
αναλογια χρονου/ορθοτητας.

Οδηγιες Μεταγλωτισης:Μπορειτε να επιλεξετε οποιαδηποτε μεταβλητη θελετε να αλλαξετε αν δεν σας ικανοποιουν οι default τιμες,και μπορειτε να επιλεξετε να
δωσετε οποιοδηποτε απο το ή τα αρχειο ή αρχεια επιθυμειτε αλλιως τα υπολοιπα θα ζητηθουν απο το προγραμμα στη συνεχεια.Ενα πιθανο τρεξιμο του προγραμματος θα ηταν
για παραδειγμα το:
./cube -d /home/user/Desktop/project1/train-images.idx3-ubyte -q /home/user/Desktop/project1/t10k-images.idx3-ubyte -k 13 -N 1 -R 15000 -probes 7 -M 200 -o /home/user/Desktop/project1mine/outputCUBE.txt

CLUSTERING

Για το Clustering χρησιμοποιουνται τα εξης αρχεια:
Clustering/main_clustering.cpp, Clustering/ClassicClustering.cpp, Clustering/ClassicClustering.h, Clustering/Clustering.cpp,Clustering/Clustering.h, Clustering/ClusteringReading.cpp, Clustering/ClusteringReading.h,Clustering/HypercubeClustering.cpp, Clustering/HypercubeClustering.h,Clustering/ImageCollection.cpp,Clustering/ImageCollection.h,Clustering/LshClustering.cpp,Clustering/LshClustering.h

Φυσικα χρησιμοποιηθηκαν και αρχεια του Cube και της LSH, καθως και συναρτησεις απο το Functions_for_both_algorithms. Το πρόγραμμα διαβάζει απο τη γραμμή εντολών το input file, το configuration file, config.txt στη συγκεκριμενη περιπτωση, το ονομα του output file που θα παραχθει, την προαιρετικη μεταβλητη complete σε περιπτωση που θελουμε εκτυπωση ολων των clusters με τα στοιχεια τους στο output file και τη μεθοδο, δηλαδη αν θα χρησιμοποιησουμε Classic,LSH, ή Hypercube(γραμμενα ετσι).
Στο config.txt εχω θεσει τιμες, ή χρησιμοποιούνται οι default. Στην περιπτωση μου, ειχα θεσει: 
number_of_clusters: 4
number_of_vector_hash_tables: 3
number_of_vector_hash_functions: 4
max_number_M_hypercube: 10
number_of_hypercube_dimensions: 3
number_of_probes: 2
Το προγραμμα ξεκιναει διαβαζοντας και καταχωρίζοντας τις εικονες (χρηση κλασης για images collection) και στη συνεχεια ξεκιναει η καταμετρηση του χρονου για το clustering και επιλεγεται ποια μεθοδος θα χρησιμοποιηθει με βαση το ορισμα που λαβαμε απο τη γραμμη εντολων. Ετσι εχουμε μια κλαση clustering που αναλογα θα καλεσει τον constructor ClassicClustering, LshClustering ή HypercubeClustering, μιας που χρησιμοποιουμε κληρονομικοτητα και εχω και τις τρεις αυτες κλασεις. Στη συνεχεια καλειται η execute, η οποια καλει αρχικα την initialize και μετα σε loop την assignment και την update και συνεχιζει ελεγχοντας ποτε πρεπει να σταματησει με τη shouldstop(να σταματαει οταν δε βρεθηκαν νεα σημεια). Η initialize και η update ειναι κοινες για τις τρεις εκδοχες, ομως η assignment ειναι διαφορετικη στην κλασικη περιπτωση(Lloyd) και διαφορετικη για τις LSH και Hypercube(Range search και Lloyd σε υποπεριπτωσεις πχ οσα περισσεψαν σημεια ή βρεθηκαν δυο φορες κτλ) χρησιμοποιωντας τον αλγοριθμο και τη θεωρια των διαφανειων. 
Συγκεκριμενα, η initialize αρχικα επιλεγει ενα τυχαιο πρωτο κεντρο και μετα δημιουργει τον πινακα Pr με τα μερικα αθροισματα. Για ενα τυχαιο αριθμο μετα, ελεγχω σε ποιο διαστημα βρισκεται και αρα βρισκω ποιο σημειο ειναι το επομενο κεντρο. Οπου βρω κεντρο, βαζω στον πινακα -1. Για την αναζητηση χρησιμοποιω binary search.
Επειτα καλειται η silhouette και γραφονται τα αποτελεσματα στο αρχειο. Για διευκολυνση μας γινονται και εκτυπωσεις στο προγραμμα.

Εντολη ενδεικτικης εκτελεσης clustering αν υποθεσουμε οτι τα αρχεια ειναι στον ιδιο φακελο:
./cluster -i t10k-images.idx3-ubyte  -c config.txt  -o output.txt -complete -m Classiic
./cluster -i t10k-images.idx3-ubyte  -c config.txt  -o output.txt -complete -m LSH
./cluster -i t10k-images.idx3-ubyte  -c config.txt  -o output.txt -complete -m Hypercube


Τα προγραμματα μας μεταγλωττιζονται με make στον αντιστοιχο φακελο.


