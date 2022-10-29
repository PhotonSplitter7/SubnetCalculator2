//***************CODE****************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//Helper functions*************************

//subnet calculator 2 functions


//getSubnetSize
int getSubnetSize(int overallSize, int numSubNets){

int subnetSize = overallSize/numSubNets;
return subnetSize;
}

//prints subnets
void printSubnets(int numSubNets, int subnetSize, int IPaddr[4], int cidrNum){

int subMask[4];
int binMask[4][8];
int bincounter =0;
int cidrAddon =0;
int subnetCidr=0;

if(numSubNets ==2)
cidrAddon=1;
if(numSubNets ==4)
cidrAddon=2;
if(numSubNets==8)
cidrAddon=3;
//calculate subnet cidr number
subnetCidr= cidrNum+cidrAddon;

//create binary subnet mask with cidr number
for(int r =0;r<4;r++){
for(int c=0;c<8;c++){
if(bincounter == cidrNum){
binMask[r][c]=0;
}
else{
binMask[r][c]=1;
}

bincounter++;
}
}

//create subnet mask decimal
BinToDec(subMask, binMask);
//counter for each subnet
int counter = 0;

for(int i = 0;i<numSubNets;i++){

//subnet header
printf("\nsubnet %d: ", (i+1));
//print net addr for subnet
printf("\nSubnet net addr: ");
printAddressDec(IPaddr);

for(int j = 1;j<subnetSize;j++){

//if ip address octet maxed out, roll over previous one
if(IPaddr[3] == 255){
IPaddr[2]+=1;
IPaddr[3] = 0;
}
//else add 1 to last octet
else{
IPaddr[3] +=1;
}
//increase counter
counter++;
}

//print and calculate subnet info here
printf("\nSubnet Broadcast is: ");
printAddressDec(IPaddr);

//print size of network
printf("\nSize of network: %d", subnetSize);
//print cidr for subnet
printf("\nCIDR prefix: /%d", subnetCidr);
//reset counter
counter = 0;

//add 1 to get next subnet net address
if(IPaddr[3] == 255){
IPaddr[2]+=1;
IPaddr[3] = 0;
}
//else add 1 to last octet
else{
IPaddr[3] +=1;
}

}
return;
}

//******************************************
int
pwr (int power)
{
 int num = 2;
 for (int i = 1; i < power; i++){
num = num * 2;
}
 if (power == 0)
 return 1;

 return num;
}
void
printAddressDec (int address[4])
{
 for (int i = 0; i < 4; i++)

{

printf ("%d", address[i]);

if (i < 3)
printf (".");

}
 return;
}
void
printAddressBin (int address[4][8])
{
 for (int j = 0; j < 4; j++)

{

for (int i = 0; i < 8; i++)
{
 printf ("%d", address[j][i]);
}

printf (".");

}
 return;
}
//converts decimal IP to Binary
void
convertToBinary (int decimalAddr[4], int BinAddr[4][8])
{
 for (int i = 0; i < 4; i++)

{

for (int j = 7; j >= 0; j--)
{
 BinAddr[i][j] = decimalAddr[i] % 2;
 decimalAddr[i] = decimalAddr[i] / 2;
}

}
 return;
}
int
getCIDRnum (int BinMask[4][8])
{
 int cidrNum = 0;
 for (int r = 0; r < 4; r++)

{

for (int c = 0; c < 8; c++)
{
 if (BinMask[r][c] == 1)
 {

cidrNum++;
 }
}

}
 return cidrNum;
}
//calculate decimal address from binary address
void
BinToDec (int decAddr[4], int binAddr[4][8])
{
 int sum = 0; //adds up power of 2 to get decimal representation of binary octet
 int power = 7; //power counts down for every column moved over
 for (int r = 0; r < 4; r++)

{

for (int c = 0; c < 8; c++)
{
 if (binAddr[r][c] == 1)
 {

sum += pwr (power);
 } //add 2^power to sum
 power--; //power goes down 1 until end where its 2^0 for 1
}
//once octet calculated above assign it to decimal gateway address

decAddr[r] = sum;

sum = 0; //reset sum for next octet

power = 7; //reset power for next octet

}
 return;
}
//function to calculate gateway from binary IP
void
IPtoGateway (int cidrNum, int IP[4][8], int Gateway[4][8])
{
 for (int r = 0; r < 4; r++)

{

for (int c = 0; c < 8; c++)
{
 if (((r * 8) + c) >= cidrNum)
 { //if dividing line reached only copy 0's into host bits

Gateway[r][c] = 0;
 }
 //if dividing line not met fill with network bits
 else
 {

Gateway[r][c] = IP[r][c];
 }
}

}
 return;
}
//function to calculate broadcast from binary IP
void
IPtoBroadcast (int cidrNum, int IP[4][8], int Broadcast[4][8])
{
 for (int r = 0; r < 4; r++)

{

for (int c = 0; c < 8; c++)
{
 if (((r * 8) + c) >= cidrNum)
 { //if dividing line reached only copy 1's into host bits

Broadcast[r][c] = 1;
 }
 //if dividing line not met fill with network bits
 else
 {

Broadcast[r][c] = IP[r][c];
 }
}

}
 return;
}
//gets ip for start address
void
getStartAddr (int gateway[4], int firstAddr[4])
{
 for (int i = 0; i < 4; i++)

{

firstAddr[i] = gateway[i];

}
 firstAddr[3] += 1; //next address to
 return;
}
//gets ip for last address
void
getEndAddr (int broadcast[4], int lastAddr[4])
{
 //copy broadcast address to last address
 for (int i = 0; i < 4; i++)

{

lastAddr[i] = broadcast[i];

}
 //subtract 1 from broadcast address
 lastAddr[3] -= 1;
 return;
}
//main function*********************************
int
main ()
{
 int flag = 1;
 char val;
 while (flag == 1)

{
//4 octets to hold binary IP address thats converted
char addrString[16];
char cidrString[3];
int numSubNets = 0;
int ipAddress[4];
int cidrNum = 0;
int BinAddr[4][8];
int subnetSize=0;
int overallSize=0;

printf ("Enter your network address:\n\n");
scanf ("%s", addrString); //get user address
sscanf (addrString, "%d.%d.%d.%d", &ipAddress[0], &ipAddress[1],&ipAddress[2], &ipAddress[3]);

//get number of subnets
printf ("Enter number of subnets:\n\n");
scanf ("%d", &numSubNets); // get subnet number


//check to make sure num of subnets are even
if((numSubNets % 2) != 0){
numSubNets +=1;
}
//only
if(numSubNets == 6)
numSubNets = 8;

printf("\nNUM OF SUBNETS = %d\n", numSubNets);

//get cidr number
printf("enter CIDR number:\n\n");
scanf("%s", cidrString);
sscanf(cidrString, "/%d", &cidrNum);

//calculate overall size of network to be divided
overallSize = pwr((32-cidrNum));

//calculate size of each subnet
subnetSize = getSubnetSize(overallSize, numSubNets);

//************************compute network addresses*****************

//calculate all subnet data and print
printSubnets(numSubNets, subnetSize, ipAddress, cidrNum);
//prompt user to go again

printf ("\nDo you wish to continue? (y/n)\n");
scanf (" %c", &val);
//if y selected loop continues

if (val == 'y' || val == 'Y')
{
 flag = 1;
}

else
{
 flag = 0;
}

}
return 0;
}