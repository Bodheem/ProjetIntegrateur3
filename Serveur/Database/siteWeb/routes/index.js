var express = require('express');
var constantes = require('../lib/constantes.js');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {

var fs = require("fs");
var file = "PainBall.db";

var sqlite3 = require("sqlite3").verbose();
var db = new sqlite3.Database(file);
/*
SELECT column_name(s)
FROM table1
INNER JOIN table2
ON table1.column_name=table2.column_name;
*/
db.all("SELECT USERNAME, CASH, AVATAR_ID, ACHIEVEMENT_POINT, GAMES_WON, GAMES_PLAYED, GAMES_COMP_WON, GAMES_COOP_WON FROM UTILISATEUR JOIN STATISTIQUES ON UTILISATEUR.USERNAME=STATISTIQUES.USER_ID WHERE IS_PUBLIC = 1", function(err, row) {
    //console.log(row.USERNAME);
    //row.AVATAR_ID = './' + row.AVATAR_ID + '.jpg';
    console.log(JSON.stringify(row));
//
   
    
    res.render('accueil', { foo: row, bar: 'really' });
     db.close();
});
 
});

/*
                                                                                        
                                      Thepathof                                         
                                  therighteousmanis                                     
                              besetonallsidesbytheiniq                                  
                      uitiesoftheself           ishandth                                
                   etyrannyofevi                  lmen.Bl                               
                 essedishewho,in                   thenam                               
                 eofcharityandgoo                   dwill                               
                 ,shepherdst heweak    throughthev  alley                               
                 ofdarkness,forheist rulyhisbrother' skee                               
                 perandthefinderof  lostchildren.AndIwill                               
                strik  edownuponth  eewithgreatvengeancea                               
               ndfuriousangerthosew howouldatte mpttopois                               
              onanddestroyMybroth   ers.AndyouwillknowMyn                               
             ameistheLordwhenIlayMyvengeanceupont  hee.T                                
            hepat          hoftherighteousman     isbese                                
           tonal                      lsidesb     ythein                                
          iquiti                                 esofth                                 
         eselfi                                 shandt                                  
        hetyra                                  nnyofe                                  
        vilme                      n.Bl        essedi                                   
        shew                      ho,in the   nameof                                    
        char                      ityandgood  will,                         shepherds   
       thewe                      akthrough  theva                        lleyofdarkne  
       ss,fo                     rheistruly hisbr                       other'    skee  
       peran                     dthefinde  roflo                     stchild    ren.A  
       ndIwi                    llstriked  ownupo                   ntheewi     thgre   
       atven                    geancean   dfuriousangerthosewh   owoulda     ttemp     
        ttop                   oisonand    destroyMybrothers.Andyouwill      knowM      
        ynam                   eistheL     ordwh   enIla   yMyvengean      ceupon       
        thee                  .Thepath      oft   herighteousmanisb      eseton         
        allsi               desby thein         iquitiesoftheselfi     shandth          
         etyr             annyo  fevilme         n.Blessedishewho,in   thenameo         
         fchar            ityandgoodwill                     ,shepher    dstheweak      
          throu            ghthevalleyo              fdar       kness,  forh eistr      
          ulyhis              brot                   her'        skeepe  randthef       
           indero                                flo              stchi    ldre         
            n.AndIwi                            llst              riked     ownu        
               ponthee                          with              greatvengeance        
     and        furiousang                       erth           osewhowouldatte         
    mpttopo    isonanddestroyMyb                  rot         hers.An    d              
    youwillknowMyn ameistheLordwhenIlayM           yven    geanceu                      
    pont hee.Thepathoft    herighteousmani sbesetonallsidesbythe                        
     iniq  uitiesofth         eselfishand thetyrannyofevilmen                           
      .Ble   ssedis         hewho,inthen ameof charityandg                              
       oodwill,sh           epherdsthew  eakt                                           
        hrought              hevalley   ofda                                            
          rkn                ess,fo    rhei                                             
                              struly  hisb                                              
                               rother'ske                                               
                                 eperand                                                
                                   the                                                  
                                                                                        
*/

router.get('/joueur/:joueurId', function(req, res, next)
{
    var id = req.params.joueurId;

    var fs = require("fs");
var file = "PainBall.db";
var exists = fs.existsSync(file);

var sqlite3 = require("sqlite3").verbose();
    var db = new sqlite3.Database(file);

// WHERE IS_PUBLIC = 1 AND
    console.log("SELECT USERNAME, AVATAR_ID FROM UTILISATEUR WHERE IS_PUBLIC = 1 AND USERNAME = " + id);

    var requestString = "SELECT USERNAME, AVATAR_ID FROM UTILISATEUR WHERE USERNAME = '" + id + "' AND IS_PUBLIC = 1";
    
    db.all(requestString, function(err, row){
    //console.log(row.USERNAME);
    //row.AVATAR_ID = './' + row.AVATAR_ID + '.jpg';
	console.log(JSON.stringify(row));

	var avatar = row[0].AVATAR_ID;
	var identite = row[0].USERNAME;
	
	if(JSON.stringify(row) == "[]")
	{
	    res.render('private');
	    db.close();
	    return;
	}

	else
	{

	    var achiev = {
	"AC11": {
		"Valeur": "AC11",
		"Titre": "Whelp.",
		"Points": "5",
		"Texte": "Obtenez 500 points en une partie solo",
		"Image": "Highscore.jpg"
	},
	"AC12": {
		"Valeur": "AC12",
		"Titre": "MLG Pro",
		"Points": "10",
		"Texte": "Obtenez 1000 points en une partie solo",
		"Image": "Highscore.jpg"
	},
	"AC13": {
		"Valeur": "AC13",
		"Titre": "IT'S OVER 9000!",
		"Points": "20",
		"Texte": "Obtenez 9000 points en une partie solo",
		"Image": "Highscore.jpg"
	},
	"AC21": {
		"Valeur": "AC21",
		"Titre": "My name is Max",
		"Points": "5",
		"Texte": "Gagnez votre première partie multijoueur cooperatif",
		"Image": "spGames.jpg"
	},
	"AC22": {
		"Valeur": "AC22",
		"Titre": "My world is fire and blood",
		"Points": "10",
	
	"Texte": "Gagnez 5 parties en mode multijoueur cooperatif",
	"Image": "spGames.jpg"
},
"AC23": {
	"Valeur": "AC23",
	"Titre": "I am awaited",
	"Points": "20",
	"Texte": "Gagnez 20 parties en mode multijoueur cooperatif",
	"Image": "spGames.jpg"
},
"AC31": {
	"Valeur": "AC31",
	"Titre": "Stuck in London",
	"Points": "5",
	"Texte": "Gagnez votre premier Shekel",
	"Image": "Cash.jpg"
},
"AC32": {
	"Valeur": "AC32",
	"Titre": "Shipping Gold",
	"Points": "10",
	"Texte": "Amassez 1000 Shekels",
	"Image": "Cash.jpg"
},
"AC33": {
	"Valeur": "AC33",
	"Titre": "Nigerian Prince",
	"Points": "20",
	"Texte": "Amassez 10 000 Shekels",
	"Image": "Cash.jpg"
},
"AC41": {
	"Valeur": "AC41",
	"Titre": "Copperhead",
	"Points": "5",
	"Texte": "Gagnez votre première partie en mode multijoueur",
	"Image": "mpGames.jpg"
},
"AC42": {
	"Valeur": "AC42",
	"Titre": "California Mountain Snake",
	"Points": "10",
	"Texte": "Gagnez 5 Parties en mode multijoueur",
	"Image": "mpGames.jpg"
},
"AC43": {
	"Valeur": "AC43",
	"Titre": "Black Mamba",
	"Points": "20",
	"Texte": "Gagnez 20 parties en mode multijoueur",
	"Image": "mpGames.jpg"
},
"AC51": {
	"Valeur": "AC51",
	"Titre": "Show-Off",
	"Points": "5",
	"Texte": "Achetez votre premier avatar sur le marketplace",
	"Image": "Avatars.jpg"
},
"AC52": {
	"Valeur": "AC52",
	"Titre": "Le Domaine",
	"Points": "10",
	"Texte": "Achetez les avatars de la famille De Touchet",
	"Image": "Avatars.jpg"
},
"AC53": {
	"Valeur": "AC53",
	"Titre": "Family Tree",
	"Points": "20",
	"Texte": "Achetez tous les avatars",
	"Image": "Avatars.jpg"
},
"AC61": {
	"Valeur": "AC61",
	"Titre": "Skript Kiddie",
	"Points": "5",
	"Texte": "Achetez votre première carte sur le marketplace",
	"Image": "maps.jpg"
},
"AC62": {
	"Valeur": "AC62",
	"Titre": "Byte Kode Injektor",
	"Points": "10",
	"Texte": "Achetez 5 cartes sur le marketplace",
	"Image": "maps.jpg"
},
"AC63": {
	"Valeur": "AC63",
	"Titre": "Data Miner",
	"Points": "20",
	"Texte": "Achetez 10 cartes sur le marketplace",
	"Image": "maps.jpg"
},
"AC70": {
	"Valeur": "AC70",
	"Multi": "0",
	"Titre": "Make America Great Again",
	"Points": "10",
	"Texte": "Creez un mur",
	"Image": "friends.jpg"
},
"AC80": {
	"Valeur": "AC80",
	"Multi": "0",
	"Titre": "Navy Seal",
	"Points": "20",
	"Texte": "gagnez une partie solo sans perdre de billes",
	"Image": "Perfect.jpg"
},
"AC90": {
	"Valeur": "AC90",
	"Multi": "0",
	"Titre": "DMCA Strike",
	"Points": "10",
	"Texte": "Sauvegardez une carte avec un droit d'auteur " ,
	"Image": "community.jpg"
},
"AC100": {
	"Valeur": "AC100",
	"Multi": "0",
	"Titre": "Git Gud",
	"Points": "5",
	"Texte": "Terminez le tutoriel",
	"Image": "gitgud.jpg"
}
};
	    
	    db.all("SELECT ACHIEVEMENT_ID, USERNAME, AVATAR_ID FROM UTILISATEUR JOIN ACHIEVEMENT_UNLOCKED ON UTILISATEUR.USERNAME=ACHIEVEMENT_UNLOCKED.USER_ID  WHERE USERNAME = '" + id + "' AND IS_PUBLIC = 1", function(err, row){


		if(JSON.stringify(row) == "[]")
		{
		    res.render('noskills');
		    return;
		}
		
		console.log(JSON.stringify(row));

		var arrpara = [];

		console.log(row[0].ACHIEVEMENT_ID);

		console.log(achiev['AC11']);

                
		
		for (index = 0; index < row.length; ++index)
		{
		    element = row[index].ACHIEVEMENT_ID;
		    
		    arrpara.push(achiev[element]);


		}

		console.log("ARRPARA : " + JSON.stringify(arrpara));


   

//var map = JSON.parse(achiev);

	//	console.log(map)
		
		
		res.render('achievment', { arrpara: arrpara, avatar: avatar, identite:identite });

	    db.close();

      
});
	}
      
});
    


});


router.get('/aide', function(req, res, next) {
    res.render('aide');
});

module.exports = router;

