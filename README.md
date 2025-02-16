# Smart-Parking-System

Danas je u prometnim dijelovima svih većih gradova dobro poznat problem pronalaska 
slobodnog parking mjesta. Kako je takav i slučaj u Sarajevu, tema našeg projekta će biti 
realizacija jednostavnog Smart Parking Sistema koji bi omogućavao da se dobije 
informacija o dostupnosti slobodnog parkinga na telefonu, putem interneta.  
Ovaj sistem ćemo realizovati korištenjem razvojnog sistema FRDM-KL25Z, matrične 
tastature,  infracrvenog senzora udaljenosti, displeja, te aplikacije.  
U nastavku je opisan način rada sistema. 
Na ulazu na parking postavljen je displej na kojem je po defaultu oznaka zabrane ulaza. 
Kada korisnik parkinga, korištenjem tastature unese tačnu kombinaciju brojeva, ulaz na 
parking mu je dozvoljen, te će na displeju dobiti poruku o slobodnom prolazu. Nakon 
ulaska na parking na displeju će se ponovo pojaviti obavijest o zabrani ulaza.  
Na svakom od parking mjesta postavljen je infracrveni senzor udaljenosti pomoću kojeg 
ćemo dobijati informaciju o tome da li je parking mjesto slobodno ili ne. Kada se automobil 
parkira na jedno od slobodnih parking mjesta senzor ga detektuje i šalje informaciju da je 
mjesto zauzeto u aplikaciji. Unutar aplikacije moguće je pregledati broj slobodnih i 
zauzetih parking mjesta. Nakon što automobil napusti parking mjesto šalje se informacija 
o njegovom oslobađanju.  
Svjesni smo da se realizacija ovog projekta mogla izvesti na efikasniji način npr. 
korištenjem rampe na ulazu i izlazu koja bi radila pomoću servo motora, kao i senzora na 
ulazu i izlazu koji bi kontrolisali otvaranje i zatvaranje rampe. Međutim, željeli smo da 
prilikom izrade projekta primijenimo što više znanja i alata koje smo naučili koristiti 
tokom semestra na laboratorijskim vježbama. 
