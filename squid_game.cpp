#include <iostream>
#include <string>
#include <vector>

using namespace std;

//We need the class user for both players and supervisors

class User
{
public:
    User()
    {
        debt = rand() % 100000 + 10000;
        weight = rand() % 100 + 50;
    }
    string name;
    string surname;
    string city;
    int debt;
    int weight;
};
class Supervisor: public User
{
public:
    string shape;
    int playersDebt;
    Supervisor()
    {
        this->debt = rand() % 100000 + 10000;
        this->weight = rand() % 100 + 50;
        this->playersDebt = 0;
    }
    Supervisor(string name, string surname, string shape)
    {
        this->name = name;
        this->surname = surname;
        this->shape = shape;
    }

    int getDebt()
    {
        return debt;
    }
    int getWeight()
    {
        return weight;
    }
    void addDebt(int debt)
    {
        this->playersDebt += debt;
    }


};
class Player: public User
{
public:
    int no;
    Supervisor* supervisor;
    Player()
    {
        this->debt = rand() % 100000 + 10000;
        this->weight = rand() % 100 + 50;
        this->supervisor = nullptr;

    }

    int getDebt()
    {
        return debt;
    }
    int getWeight()
    {
        return weight;
    }
    int getNo()
    {
        return no;
    }
    Supervisor* getSupervisor()
    {
        return this->supervisor;
    }
    void setSupervisor(Supervisor *supervisor)
    {
        this->supervisor = supervisor;
    }
    void die()
    {
        if(supervisor != nullptr)
        {
            Supervisor* toBeUpdated = this->supervisor;
            toBeUpdated->addDebt(this->debt);
        }
    }


};


 //Used to calculate the total weight of a number of players
int calculateWeight(vector<Player*> players)
{
    int totalWeight = 0;
    for(int i = 0; i < players.size(); i++)
    {
        totalWeight += players[i]->getWeight();
    }
    return totalWeight;
}

//First game that removes the users with the id an even number
void redLightGreenLight(vector<Player*> &players)
{
    for (int i =0; i < 99; i++)
    {
        if(players[i]->no %2 != 1)
        {
            players[i]->die();
            players.erase(players.begin() + i);
        }
    }
}
void eliminatePlayers(vector<Player*> players)
{
    for(int i =0 ; i < players.size(); i++)
    {
        players[i]->die();
    }
}
void addAll(vector<Player*> &to, vector<Player*> from)
{
    for(Player* pl : from)
    {
        to.push_back(pl);
    }
}
void tugOfWar(vector<Player*> &players)
{
    vector<Player*> team1;
    vector<Player*> team2;
    vector<Player*> team3;
    vector<Player*> team4;
    vector<Player*> finalTeam;
    int teamSize = players.size() /4;
    for (int i =0; i < teamSize*4; i++) //we want to keep the last players if they can't be equally separated into 4 groups
    {
        if( i < teamSize)
        {
            team1.push_back(players[i]);
        }
        else if (i >= teamSize && i < teamSize*2)
        {
            team2.push_back(players[i]);
        }
        else if (i >= teamSize *2 && i < teamSize *3)
        {
            team3.push_back(players[i]);
        }
        else
        {
            team4.push_back(players[i]);
        }
    }
    int team1Weight = calculateWeight(team1);
    int team2Weight = calculateWeight(team2);
    int team3Weight = calculateWeight(team3);
    int team4Weight = calculateWeight(team4);
    if( team1Weight <= team2Weight)
    {
        eliminatePlayers(team1);
        addAll(finalTeam,team2);
    }
    else
    {
        eliminatePlayers(team2);
        addAll(finalTeam,team1);
    }
    if(team3Weight <= team4Weight)
    {
        eliminatePlayers(team3);
        addAll(finalTeam,team4);
    }
    else
    {
        eliminatePlayers(team4);
        addAll(finalTeam,team3);
    }

    for (int i = teamSize*4; i < players.size(); i++)
    {
        finalTeam.push_back(players[i]);
    }

    players = finalTeam;

}

//each player has a random number and the one that has the biggest number is eliminated
void marbles(vector<Player*> &players)
{
    int var1, var2;
    int n = players.size();
    vector<Player*> finalTeam;
    if( n%2 != 0 )
    {
        for (int i =0; i < n-2; i=i+2)
        {
            var1= rand() % 10;
            var2= rand() % 10;
            if(var1 >  var2)
            {
                players[i]->die();
                finalTeam.push_back(players[i+1]);
            }
            else
            {
                players[i+1]->die();
                finalTeam.push_back(players[i]);
            }

        }
        finalTeam.push_back(players[n-1]);
    }
    else
    {
        for (int i =0; i < n-1; i=i+2)
        {
            var1= rand() % 10;
            var2= rand() % 10;

            if(var1 >  var2)
            {
                players[i]->die();
                finalTeam.push_back(players[i+1]);
            }
            else
            {
                players[i+1]->die();
                finalTeam.push_back(players[i]);
            }
        }
    }
    players = finalTeam;
}

Player* genken(vector<Player*> &players)
{
    int i, var1, var2;
    Player* winner = new Player();
    winner->no = players[0]->no;
    winner->name= players[0]->name;
    winner->surname= players[0]->surname;
    winner->city = players[0]->city;

    for(i=1; i<players.size(); i++)
    {
        var1= rand() % 3 + 1;
        var2= rand() % 3 + 1;
        while(var1 == var2)
        {
            var1= rand() % 3 + 1;
            var2= rand() % 3 + 1;
        }
        if(var1 == 1 && var2 == 2)
        {
            winner->no = players[i]->no;
            winner->name= players[i]->name;
            winner->surname= players[i]->surname;
            winner->city = players[i]->city;
        }

        if(var1 == 2 && var2 == 3)
        {
            winner->no = players[i]->no;
            winner->name= players[i]->name;
            winner->surname= players[i]->surname;
            winner->city = players[i]->city;
        }

        if(var1 == 3 && var2 == 1)
        {
            winner->no = players[i]->no;
            winner->name= players[i]->name;
            winner->surname= players[i]->surname;
            winner->city = players[i]->city;
        }


    }

    return winner;


}
int main()
{


    string names1[108] = { "David","John","Paul","Mark","James","Andrew","Scott","Steven","Robert","Stephen","William","Craig","Michael","Stuart","Christopher","Alan","Colin","Brian","Kevin","Gary","Richard",
                           "Derek","Martin","Thomas","Neil","Barry","Ian","Jason","Iain","Gordon","Alexander","Graeme","Peter","Darren","Graham",
                           "George","Kenneth","Allan","Simon","Douglas","Keith","Lee","Anthony","Grant","Ross","Jonathan","Gavin","Nicholas","Joseph","Stewart",
                           "Nicola","Karen","Fiona","Susan","Claire","Sharon","Angela","Gillian","Julie","Michelle","Jacqueline","Amanda","Tracy","Louise","Jennifer","Alison",
                           "Sarah","Donna","Caroline","Elaine","Lynn","Margaret","Elizabeth","Lesley","Deborah","Pauline","Lorraine","Laura","Lisa","Tracey","Carol","Linda","Lorna","Catherine",
                           "Wendy","Lynne","Yvonne","Pamela","Kirsty","Jane","Emma","Joanne","Heather","Suzanne","Anne","Diane","Helen","Victoria","Dawn","Mary","Samantha","Marie","Kerry","Ann",
                           "Hazel","Christine","Gail","Andrea"
                         };
    string names2[108] = { "COLEMAN","BUTLER","SMITH","JOHNSON","WILLIAMS","BROWN","JONES","GARCIA","MILLER","DAVIS","RODRIGUEZ","MARTINEZ","HERNANDEZ","LOPEZ",
                           "GONZALEZ","WILSON","ANDERSON","THOMAS","TAYLOR","MOORE","JACKSON","MARTIN","LEE","PEREZ","THOMPSON","WHITE","HARRIS","SANCHEZ","CLARK","RAMIREZ","LEWIS","ROBINSON",
                           "WALKER","YOUNG","ALLEN","KING","WRIGHT","SCOTT","TORRES","NGUYEN","HILL","FLORES","GREEN","ADAMS","NELSON","BAKER","HALL","RIVERA","CAMPBELL","MITCHELL","CARTER","ROBERTS",
                           "GOMEZ","PHILLIPS","EVANS","TURNER","DIAZ","PARKER","CRUZ","EDWARDS","COLLINS","REYES","STEWART","MORRIS","MORALES","MURPHY","COOK","ROGERS",
                           "GUTIERREZ","ORTIZ","MORGAN","COOPER","PETERSON","BAILEY","REED","KELLY","HOWARD","RAMOS","KIM","COX","WARD","RICHARDSON","WATSON","BROOKS","CHAVEZ",
                           "WOOD","JAMES","BENNETT","GRAY","MENDOZA","RUIZ","HUGHES","PRICE","ALVAREZ","CASTILLO","SANDERS","PATEL","MYERS","LONG","ROSS","FOSTER","JIMENEZ","POWELL","JENKINS",
                           "PERRY","RUSSELL","SULLIVAN","BELL"
                         };

    string places[108] = { "NewYork","LosAngeles","Chicago","Houston","Phoenix","Philadelphia","SanAntonio","SanDiego","Dallas","SanJose","Detroit","Jacksonville",
                           "Indianapolis","SanFrancisco","Columbus","Austin","Memphis","FortWorth","Baltimore","Charlotte","ElPaso","Boston","Seattle","Washington","Milwaukee","Denver",
                           "Louisville/JeffersonCounty","LasVegas","Nashville-Davidson","OklahomaCity","Portland","Tucson","Albuquerque","Atlanta","LongBeach","Fresno","Sacramento","Mesa",
                           "KansasCity","Cleveland","VirginiaBeach","Omaha","Miami","Oakland","Tulsa","Honolulu","Minneapolis","ColoradoSprings","Arlington","Wichita","Raleigh","St.Louis",
                           "SantaAna","Anaheim","Tampa","Cincinnati","Pittsburgh","Bakersfield","Aurora","Toledo","Riverside","Stockton","CorpusChristi","Newark","Anchorage","Buffalo","St.Paul",\
                           "Lexington-Fayette","Plano","FortWayne","St.Petersburg","Glendale","JerseyCity","Lincoln","Henderson","Chandler","Greensboro","Scottsdale","BatonRouge","Birmingham",
                           "Norfolk","Madison","NewOrleans","Chesapeake","Orlando","Garland","Hialeah","Laredo","ChulaVista","Lubbock","Reno","Akron","Durham","Rochester","Modesto","Montgomery",
                           "Fremont","Shreveport","Arlington","Glendale","Madrid","Almeria","Vera","Turre","Granada","Garrucha","Andalucia","Morenos"
                         };


    vector<Player*> players;

    //we need a copy of players in order to not modify the list of users
    vector<Player*> playersCopy;
    vector<Supervisor*>supervisors;
    Player* winner = new Player();
    Supervisor* supervisor = new Supervisor();
    int  money = 0;
    int moneySup[9] = {0};
    int moneyTri=0, moneyCir=0, moneySqu=0;
    string richestTeam;
    int money2;

    //to create the vector of players
    int vectorNo[99];
    for (int i = 0; i< 99; i++)

    {
        Player* player = new Player();
        player->no = i+1;
        player->name= names1[i];
        player->surname= names2[i];
        player->city = places[i];
        player->weight = rand() % 100 + 50;
        player->debt = rand() % 100000 + 10000;
        players.push_back(player);
        playersCopy.push_back(player);

    }

    //to assign a supervisor to each player

    int playersAssigned = 0;
    for (int i = 0; i< 9; i++)
    {
        Supervisor* supervisor = new Supervisor();
        if(i <3 )
        {
            supervisor->shape = "triangle";
        }
        else if ( i >= 3 && i < 6)
        {
            supervisor->shape = "square";
        }
        else
        {
            supervisor->shape = "circle";
        }
        supervisor->name = names1[i];
        supervisor->surname = names2[i];
        supervisor->weight = rand() % 100 + 50;
        supervisor->debt = rand() % 100000 + 10000;
        supervisors.push_back(supervisor);
        int lastToBeAssigned = playersAssigned + 11;
        while(playersAssigned <lastToBeAssigned )
        {
            players[playersAssigned]->setSupervisor(supervisor);
            playersAssigned++;
        }
    }


    redLightGreenLight(players);
    cout << "The winners of the first game are:" << endl;
 for (int j=0; j< players.size(); j++)
cout << players[j]->no << endl << players[j]->name<< endl << players[j]->surname << endl << players[j]->city << endl;

    tugOfWar(players);
    cout << "The winners of the second game are:" << endl;

for (int j=0; j< players.size(); j++)
cout << players[j]->no << endl << players[j]->name<< endl << players[j]->surname << endl << players[j]->city << endl;

    marbles(players);
    cout << "The winners of the third game are:" << endl;


for (int j=0; j< players.size(); j++)
cout << players[j]->no << endl << players[j]->name<< endl << players[j]->surname << endl << players[j]->city << endl;

    cout<< "The  winner is "<< endl;

    winner = genken(players);
    cout << winner->name<< endl << winner->surname<< endl;


    for(int i=0; i< playersCopy.size(); i++)
    {
        if(playersCopy[i]->no != winner->no)
        {
            money += playersCopy[i] -> debt;

            supervisor = playersCopy[i] -> getSupervisor();

            int j = 0;
            while (supervisors[j]->name != supervisor->name)
                j++;
            moneySup[j] += playersCopy[i] -> debt;
        }
        else
        {
            int j = 0;
            while (supervisors[j]->name != supervisor->name)
                j++;
            moneySup[j] += 10 * playersCopy[i] -> debt;
        }
    }

    cout << money << endl;
    for (int j=0; j<9; j++)
    {
        moneySup[j] -= supervisors[j]->debt;
        supervisors[j]->debt = moneySup[j];
    }

    for (int i=0; i<9; i++)
    {
        for( int j=i+1; j<9; j++)
        {
            int aux = 0;
            if (supervisors[i]->debt < supervisors[j]->debt)
            {
                aux = supervisors[i]->debt;
                supervisors[i]->debt = supervisors[j]->debt;
                supervisors[j]->debt = aux;
            }

        }
    }

    for (int i=0; i<9; i++)
    {
        if(supervisors[i]->shape == "triangle")
            moneyTri += supervisors[i]->debt;
        if(supervisors[i]->shape == "circle")
            moneyCir += supervisors[i]->debt;
        if(supervisors[i]->shape == "square")
            moneySqu += supervisors[i]->debt;
    }

    if (moneySqu > moneyCir){
        richestTeam = "square";
        money2 = moneySqu;
    }
    else richestTeam = "circle";

{
    money2 = moneyCir;
}
    if( money2 < moneyTri)

        {richestTeam= "triangle";
        money2 = moneyTri;
        }

        cout << "The richest team is "<< richestTeam << endl;
    return 0;
}

