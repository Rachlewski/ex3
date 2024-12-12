/******************
Name:Yoav Rachlewski
ID:327695169
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
void insertSales( int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day, int brand){
    if(brand>=0 && brand<NUM_OF_BRANDS){
        scanf(" %d %d %d %d",&arr[day][brand][0], &arr[day][brand][1],
&arr[day][brand][2], &arr[day][brand][3]);
    }
    else {
        printf("This brand is not valid");
    }
}
int isDayFull(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    for(int brand=0; brand<NUM_OF_BRANDS; brand++) {
        for(int type=0; type<NUM_OF_TYPES; type++) {
            if(arr[day][brand][type]==-1) {
                return 0;
            }
        }
    }
    return 1;
}
int findDailyTypeSales(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int type) {
    int total = 0;
    for(int brand=0; brand<NUM_OF_BRANDS; brand++) {
        total+=arr[day][brand][type];
    }
    return total;
}
int findDailyBrandSales(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand) {
    int total = 0;
    for(int type=0; type<NUM_OF_TYPES; type++) {
        total+=arr[day][brand][type];
    }
    return total;
}
int findBestSoldBrand(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int bestSold = 0;
    for(int brand=0; brand<NUM_OF_BRANDS; brand++) {
        if(findDailyBrandSales(arr,day,brand)>bestSold) {
            bestSold = brand;
        }
    }
    return bestSold;
}
int findBestSoldType(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int bestSold = 0;
    for(int type=0; type<NUM_OF_TYPES; type++) {
        if(findDailyTypeSales(arr,day,type)>bestSold) {
            bestSold = type;
        }
    }
    return bestSold;
}
int findDailySales(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day) {
    int total = 0;
    for(int type=0; type<NUM_OF_TYPES; type++) {
        total+=findDailyTypeSales(arr,day,type);
    }
    return total;
}
int findOverallBrandSales(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int brand) {
    int total = 0;
    for(int day=0; day<days; day++ ) {
        total+=findDailyBrandSales(arr,day,brand);
    }
    return total;
}
int findOverallTypeSales(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days, int type) {
    int total = 0;
    for(int day=0; day<days; day++ ) {
        total+=findDailyTypeSales(arr,day,type);
    }
    return total;
}
int findMostProfitDay(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days) {
    int  bestDay= 0;
    for(int day=0; day<days; day++) {
        if(findDailySales(arr,day)>bestDay) {
            bestDay = day;
        }
    }
    return bestDay;
}
int findBestType(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days) {
    int bestType = 0;
    for(int type=0; type<NUM_OF_TYPES; type++) {
        if(findOverallTypeSales(arr,days,type)>bestType) {
            bestType = type;
        }
    }
    return bestType;
}
int findBestBrand(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days) {
    int bestBrand = 0;
    for(int brand=0; brand<NUM_OF_BRANDS; brand++) {
        if(findOverallBrandSales(arr,days,brand)>bestBrand) {
            bestBrand = brand;
        }
    }
    return bestBrand;
}
int findBrandDelta(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int days,int brand) {
    int delta = 0;
    for(int day=1; day<days; day++) {
        delta+=findDailyBrandSales(arr,day,brand)-findDailyBrandSales(arr,day-1,brand);
    }
    return delta;
}


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    for(int i = 0; i < DAYS_IN_YEAR; i++){
        for(int j = 0; j < NUM_OF_BRANDS; j++){
            for(int k = 0; k < NUM_OF_TYPES; k++){
                cube[i][j][k] = -1;
            }
        }
    }
    int days[NUM_OF_BRANDS] = {0};
    int day = 0;
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                int brand = 0;
                scanf("%d", &brand);
                insertSales(cube,days[brand],brand);
                break;
            case addAll:
                while(!isDayFull(cube,days[0])) {
                    printf("No data for brands ");
                    for(int brand=0; brand<NUM_OF_BRANDS; brand++) {
                        if(cube[days[0]][brand][0]==-1) {
                            printf("%s ", brands[brand]);
                        }
                    }
                    printf("\nPlease complete the data\n");
                    int brand = 0;
                    scanf("%d", &brand);
                    insertSales(cube,days[0],brand);
                }
                for(int brand=0; brand<NUM_OF_BRANDS; brand++) {
                    days[brand]++;
                }
                break;
            case stats:
                printf("What day would you like to analyze?\n");
                scanf("%d", &day);
                while(day>=DAYS_IN_YEAR||day<0||day>days[0]) {
                    printf("Please enter a valid day.\nWhich day would you like to analyze?\n");
                    scanf("%d", &day);
                }
                day--;
                int totalSales = findDailySales(cube,day);
                int bestSoldBrand = findBestSoldBrand(cube,day);
                int bestSoldType = findBestSoldType(cube,day);
                day++;
                printf("In day number %d:\nThe sales total was %d\n",day,totalSales);
                printf("The best sold brand with %d sales was %s\n",findDailyBrandSales(cube,day,bestSoldBrand),
                    brands[bestSoldBrand]);
                printf("The best sold type with %d sales was %s\n",findDailyTypeSales(cube,day,bestSoldType),
                    types[bestSoldType]);
                break;
            case print:
                printf("*****************************************\n\n");
                for(int brand=0; brand<NUM_OF_BRANDS; brand++) {
                    printf("Sales for %s:\n",brands[brand]);
                    for(int day=0; day<days[0]; day++) {
                        printf("Day %d-",day+1);
                        for(int type=0; type<NUM_OF_TYPES; type++) {
                            printf("%s: %d ", types[type], cube[day][brand][type]);
                        }
                        printf("\n");
                    }
                }
                break;
            case insights:
                int bestBrand=findBestBrand(cube,days[0]);
                int bestType=findBestType(cube,days[0]);
                int bestDay=findMostProfitDay(cube,days[0]);
                printf("The best-selling brand overall is %s:%d$\n",brands[bestBrand],
                    findOverallBrandSales(cube,days[0],bestBrand));
                printf("The best-selling type of car is %s:%d$\n",
                    types[bestType],findOverallTypeSales(cube,days[0],bestType));
                printf("The most profitable day was day number %d:%d$\n",bestDay+1,findDailySales(cube,bestDay));
                break;
            case deltas:
                for(int brand=0; brand<NUM_OF_BRANDS; brand++) {
                    float delta = findBrandDelta(cube,days[0],brand);
                    float denominator  = days[0]-1;
                    float avgDelta = delta/denominator ;
                    printf("Brand: %s, Average Delta:%f\n",brands[brand],avgDelta);
                }
                break;
                default:
                    printf("Invalid input\n");
            }
            printMenu();
            scanf("%d", &choice);
        }
        printf("Goodbye!\n");
        return 0;
    }



