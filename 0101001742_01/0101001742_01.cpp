//Khai báo thư viện và cấu trúc
#include<stdio.h>
#include<iostream>
#include<iomanip>
using namespace std;

struct process
{
    int ma_tientrinh, tgcho, tgxuly, tong_tgian, tgxuathien;
}p[20];

struct Process {
    char name[10];
    int timeRL, timeCPU, priority;
    int timeOUT, timeIN, timewait, timesave;
    int index;
};

typedef Process* ListP;
int quantum;

//Khai báo hàm con
void input(ListP& pr, int& n, int& timeOUT);
void output_input(ListP pr, int n);
void output_PRIORITY_nopreemptive(ListP pr, ListP RL, int n, int m, int timeOUT);
void OUTPUT(ListP pr, ListP RL, int n, int m, int timeOUT, int set);
void process_PRIORITY_nopreemptive(ListP& pr, ListP& RL, int n, int& m, int timeOUT);
void PROCESS(ListP& pr, ListP& RL, int n, int& m, int timeOUT, int set);

//Thân hàm chính
int main()
{
    int chon;    ListP pr, RL;
    int timeOUT = 0;
    int i, j, n, m, time, remain, flag = 0, ts;
    int sum_wait = 0, sum_turnaround = 0, at[10], bt[10], rt[10];
    int tong_tgcho = 0, tong_tghoantat = 0, tg_cho_tb, tg_hoantat_tb, tgxuathien;
    do
    {
        cout << "=================================================================" << endl;
        cout << "=				MENU				=" << endl;
        cout << "=================================================================" << endl;
        cout << "=		1. Giai thuat FCFS		         	=" << endl;
        cout << "=		2. Giai thuat SJF		        	=" << endl;
        cout << "=		3. Giai thuat ROUNDROBIN	        	=" << endl;
        cout << "=		4. Giai thuat PRIORITY	        		=" << endl;
        cout << "=		0.thoat chuong trinh!!!				=" << endl;
        cout << "=================================================================" << endl;
        cout << "Nhap chuong trinh ma ban muon chon: ";
        cin >> chon;
        cout << endl;
        system("cls");
        switch (chon)
        {
        case 1:
        {
            cout << "Nhap so tien trinh: ";
            cin >> n;
            for (i = 1; i <= n; i++)
            {
                cout << "Nhap ma dinh danh tien trinh: ";
                cin >> p[i].ma_tientrinh;
                cout << "Nhap thoi gian xu ly cua tien trinh: ";
                cin >> p[i].tgxuly;
            }
            p[1].tgcho = 0;
            p[1].tong_tgian = p[1].tgxuly;
            for (i = 2; i <= n; i++)
            {
                for (j = 1; j < i; j++)
                {
                    p[i].tgcho = p[i].tgcho + p[j].tgxuly;
                }
                tong_tgcho = tong_tgcho + p[i].tgcho;
                p[i].tong_tgian = p[i].tgcho + p[i].tgxuly;
                tong_tghoantat = tong_tghoantat + p[i].tong_tgian;
            }
            tg_hoantat_tb = tong_tghoantat / n;
            tg_cho_tb = tong_tgcho / n;
            cout << setw(10) << left << "TT" << setw(10) << left << "TG - XuLy" << setw(10) << left << "TG - Cho" << setw(10) << left << "Tong" << endl;
            for (i = 1; i <= n; i++)
            {
                cout << setw(10) << left << p[i].ma_tientrinh << setw(10) << left << p[i].tgxuly << setw(10) << left << p[i].tgcho << setw(10) << left << p[i].tong_tgian;
                cout << endl;
            }
            cout << "Thoi gian trung binh: " << tg_cho_tb << endl;
            cout << "Thoi gian hoan tat trung binh: " << tg_hoantat_tb;
            cout << endl;
            break;
        }
        case 2:
        {
            cout << "Nhap so tien trinh: ";
            cin >> n;
            for (i = 1; i <= n; i++)
            {
                cout << "Nhap ma dinh danh tien trinh: ";
                cin >> p[i].ma_tientrinh;
                cout << "Nhap thoi gian xu ly cua tien trinh: ";
                cin >> p[i].tgxuly;
                cout << "Nhap thoi diem den cua tien trinh: ";
                cin >> p[i].tgxuathien;
            }
            p[1].tgcho = 0;
            p[1].tong_tgian = p[1].tgxuly;
            for (i = 2; i < n; i++)
            {
                for (j = i + 1; j <= n; j++)
                {
                    if (p[i].tgxuathien > p[j].tgxuathien)
                        swap(p[i], p[j]);
                }
            }
            for (i = 2; i <= n; i++)
            {
                for (j = 1; j < i; j++)
                {
                    p[i].tgcho = p[i].tgcho + p[j].tgxuly;
                }
                tong_tgcho = tong_tgcho + p[i].tgcho;
                p[i].tong_tgian = p[i].tgcho + p[i].tgxuly;
                tong_tghoantat = tong_tghoantat + p[i].tong_tgian;
            }
            tg_hoantat_tb = tong_tghoantat / n;
            tg_cho_tb = tong_tgcho / n;
            cout << setw(10) << left << "TT" << setw(10) << left << "TG - XuLy" << setw(10) << left << "TG - Cho" << setw(10) << left << "Tong" << endl;
            for (i = 1; i <= n; i++)
            {
                cout << setw(10) << left << p[i].ma_tientrinh << setw(10) << left << p[i].tgxuly << setw(10) << left << p[i].tgcho << setw(10) << left << p[i].tong_tgian;
                cout << endl;
            }
            cout << "Thoi gian trung binh: " << tg_cho_tb << endl;
            cout << "Thoi gian hoan tat trung binh: " << tg_hoantat_tb;
            cout << endl;
        }
        break;
        case 3:
        {
            printf("Nhap so tien trinh: ");
            scanf_s("%d", &n);
            remain = n;
            for (i = 0; i < n; i++)
            {

                printf("Nhap thoi diem den cua tien trinh %d: ", i + 1);
                scanf_s("%d", &at[i]);
                printf("Nhap thoi gian xu ly cua tien trinh %d: ", i + 1);
                scanf_s("%d", &bt[i]);
                rt[i] = bt[i];
            }
            printf("Nhap phan thoi gian(quantum): ");
            scanf_s("%d", &ts);
            printf("\n\nTien trinh|tg xu ly\t|tg cho\n\n");
            for (time = 0, i = 0; remain != 0;)
            {
                if (rt[i] <= ts && rt[i] > 0)
                {
                    time += rt[i];
                    rt[i] = 0;
                    flag = 1;
                }
                else if (rt[i] > 0)
                {
                    rt[i] -= ts;
                    time += ts;
                }
                if (rt[i] == 0 && flag == 1)
                {
                    remain--;
                    printf("P[%d]\t|\t%d\t|\t%d\n", i + 1, time - at[i], time - at[i] - bt[i]);
                    sum_wait += time - at[i] - bt[i];
                    sum_turnaround += time - at[i];
                    flag = 0;
                }
                if (i == n - 1)
                    i = 0;
                else if (at[i + 1] <= time)
                    i++;
                else
                    i = 0;
            }
            printf("\nThoi gian cho trung binh: %f\n", sum_wait * 1.0 / n);
            printf("Thoi gian hoan tat trung binh: %f", sum_turnaround * 1.0 / n);
            cout << endl;
            break;
        }
        case 4:
        {
            cout << "Nhap so Tien trinh thuc thi : \t";
            cin >> n;
            cout << "\nquantum = "; cin >> quantum;
            pr = new Process[n];
            cout << "\nNhap Ten - thoi gian den - thoi gian xu li - do uu tien cua moi Tien trinh:\n\n";
            for (int i = 0; i < n; i++)
            {

                cout << "TT" << i + 1 << ":\t";
                cin >> pr[i].name >> pr[i].timeRL >> pr[i].timeCPU >> pr[i].priority;
                if (timeOUT < pr[i].timeRL)
                    timeOUT = pr[i].timeRL + pr[i].timeCPU;
                else
                    timeOUT += pr[i].timeCPU;
                pr[i].index = i;
            }
            output_input(pr, n);
            process_PRIORITY_nopreemptive(pr, RL, n, m, timeOUT);
            output_PRIORITY_nopreemptive(pr, RL, n, m, timeOUT);
            cout << endl;
        }
        break;
        }
    } while (chon != 0);
    system("pause");
    return 0;
}

//Thân hàm con
void in(ListP& pr, int& n, int& timeOUT)
{
    timeOUT = 0;
    cout << "Nhap so Tien trinh thuc thi : \t";
    cin >> n;
    cout << "\nquantum = "; cin >> quantum;
    pr = new Process[n];
    cout << "\nNhap Ten - thoi gian den - thoi gian xu li - do uu tien cua moi Tien trinh:\n\n";
    for (int i = 0; i < n; i++)
    {

        cout << i + 1 << ":\t";
        cin >> pr[i].name >> pr[i].timeRL >> pr[i].timeCPU >> pr[i].priority;
        if (timeOUT < pr[i].timeRL)
            timeOUT = pr[i].timeRL + pr[i].timeCPU;
        else
            timeOUT += pr[i].timeCPU;
        pr[i].index = i;
    }
}

void output_input(ListP pr, int n) {
    cout << endl << "---------------INPUT---------------" << endl << endl;
    cout << "Ten | " << setw(10) << "Thoi gian den | " << setw(10) << "Thoi gian xu li | " << setw(10)
        << "do uu tien" << endl;
    for (int i = 0; i < n; i++)
        cout << pr[i].name << setw(10) << pr[i].timeRL << setw(15)
        << pr[i].timeCPU << setw(15) << pr[i].priority << endl;
    cout << "quantum = " << quantum << endl;
    cout << endl << "---------------OUTPUT---------------" << endl << endl;
}

void output_PRIORITY_nopreemptive(ListP pr, ListP RL, int n, int m, int timeOUT)
{
    cout << "PRIORITY khong doc quyen" << endl << endl;
    cout << "Ten |" << setw(10) << " Thoi gian den |" << setw(10) << " Thoi gian xu ly |"
        << setw(10) << " Thoi gian cho |" << setw(10) << " Thoi gian hoan tat" << endl;
    for (int i = 0; i < n; i++)
        cout << pr[i].name << setw(10) << pr[i].timeRL << setw(20)
        << pr[i].timeCPU << setw(15) << pr[i].timewait << setw(15) << pr[i].timesave << endl;

}

void process_PRIORITY_nopreemptive(ListP& pr, ListP& RL, int n, int& m, int timeOUT)
{
    RL = new Process;
    ListP pr1 = pr;
    process temp;
    int j = 0;
    m = 0;
    int temptime = 0;
    for (int t = 0; t <= timeOUT; t++) {
        if (m > 0 && j < m) {
            if (temptime < RL[j].timeCPU)
                temptime++;
            if (temptime == RL[j].timeCPU) {
                RL[j].timeIN = t - RL[j].timeCPU;
                RL[j].timeOUT = RL[j].timeIN + RL[j].timeCPU;
                RL[j].timewait = RL[j].timeOUT - (RL[j].timeRL + RL[j].timeCPU);
                RL[j].timesave = RL[j].timeOUT - RL[j].timeRL;
                pr1[RL[j].index].timeOUT = t;
                pr1[RL[j].index].timewait = pr1[RL[j].index].timeOUT
                    - (pr1[RL[j].index].timeRL + pr1[RL[j].index].timeCPU);
                pr1[RL[j].index].timesave = pr1[RL[j].index].timeOUT - pr1[RL[j].index].timeRL;

                temptime = 0;
                j++;
            }
        }
        for (int i = 0; i < n; i++)
            if (t == pr1[i].timeRL) {
                m++;
                int k = m - 1;
                RL = (Process*)realloc(RL, m * sizeof(Process));
                if (temptime > 0 && pr1[i].priority < RL[j].priority) {
                    m++;
                    k = m - 1;
                    RL = (Process*)realloc(RL, m * sizeof(Process));
                    for (k = m - 1; k > j + 1; k--)
                        RL[k] = RL[k - 2];
                    RL[j + 1] = pr1[i];

                    RL[j + 2] = RL[j];
                    RL[j + 2].timeCPU -= temptime;

                    RL[j].timeIN = t - temptime;
                    RL[j].timeOUT = t;
                    RL[j].timeCPU = temptime;
                    temptime = 0;
                    j++;
                }
                else {
                    while (k > j && pr1[i].priority < RL[k - 1].priority) {
                        RL[k] = RL[k - 1];
                        k--;
                    }
                    RL[k] = pr1[i];
                }
            }
    }
}
