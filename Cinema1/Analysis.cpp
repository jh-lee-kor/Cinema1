#include "Analysis.h"

#include <iostream>
using namespace std;

void Analysis::run(Database& db) {
	int i;
	bool flag = false;
	
	while (!flag) {
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "���� �¼� �м� �޴��Դϴ�." << endl;
		cout << endl;
		cout << endl;
		cout << "1. ���� ���� ���ŵ� �¼�" << endl;
		cout << endl;
		cout << "2. �¼��� ���� ����" << endl;
		cout << endl;
		cout << "3. ���ư���" << endl;
		cout << endl;
		cout << "�޴��� �Է����ֽʽÿ�. : ";
		cin >> i;

		switch (i) { // �޴� ����
		case 1:
			statistics(db);
			break;

		case 2:
			seatinfo(db);
			break;

		case 3:
			flag = true;
			break;

		default:
			cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
			break;
		}
	}
}

void Analysis::statistics(Database& db) {
	int i;
	bool flag = false;
	while (!flag) {
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�ֱ� �����ϰ� ���� ���� ���ŵ� �¼� 3���� ã���ϴ�." << endl;
		cout << endl;
		cout << endl;
		cout << "1. ��ü �󿵰� ���� ���� ���ŵ� �¼� Top3" << endl;
		cout << endl;
		cout << "2. �󿵰��� ���� ���� ���ŵ� �¼� Top3" << endl;
		cout << endl;
		cout << "3. ��ȭ�� ���� ���� ���ŵ� �¼� Top3" << endl;
		cout << endl;
		cout << "4. ���ະ ���� ���� ���ŵ� �¼� Top3" << endl;
		cout << endl;
		cout << "5. ���ư���" << endl;
		cout << endl;
		cout << "�޴��� �Է����ֽʽÿ�. : ";
		cin >> i;

		switch (i) { // �޴� ����
		case 1:
			rank_total(db);
			break;

		case 2:
			rank_theater(db);
			break;

		case 3:
			rank_movie(db);
			break;

		case 4:
			rank_gender(db);
			break;

		case 5:
			flag = true;
			break;

		default:
			cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
			break;
		}
	}
}

void Analysis::seatinfo(Database& db) {
	int i;
	bool flag = false;
	while (!flag) {
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "������ �¼��� ������ ã���ϴ�." << endl;
		cout << endl;
		cout << endl;
		cout << "1. ��ȭ�� ���� Ƚ��" << endl;
		cout << endl;
		cout << "2. ���� ���� ����" << endl;
		cout << endl;
		cout << "3. �󿵴뺰 ���� Ƚ��" << endl;
		cout << endl;
		cout << "4. ���ư���" << endl;
		cout << endl;
		cout << "�޴��� �Է����ֽʽÿ�. : ";
		cin >> i;

		switch (i) { // �޴� ����
		case 1:
			movie_count(db);
			break;

		case 2:
			gender_ratio(db);
			break;

		case 3:
			time_count(db);
			break;

		case 4:
			flag = true;
			break;

		default:
			cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
			break;
		}
	}
}

void Analysis::rank_total(Database& db) {
	
	int today = db.getbusiday() - 1;
	int countarr[8][8] = { 0 };
	// ���� Ƚ�� �˻�
	for (int day = today - 6 ; day <= today; day++) // day ����
		for (int p = 0; p < 40; p++) // ���α׷� DB ��ü ���� (40��)
			for (int r = 0; r < 8; r++)
				for (int c = 0; c < 8; c++)
					if (db.prodb[day][p].getseatuser(r, c)) { // 0�ϰ�� false, �� ���� ��� true
						countarr[r][c]++;
					}
	// �˻��� �ڷḦ ���� ū 3�� ����
	cout << "-------------------------------------------------" << endl;
	cout << "���� ���Ű� ���� �� �¼��� ������ �����ϴ�." << endl;
	top3_show(countarr);
}

void Analysis::rank_movie(Database& db) {

	cout << "-------------------------------------------------" << endl;
	cout << "�� ��ȭ������ �������� ��ȭ�� ������ �����ϴ�." << endl;
	cout << "-------------------------------------------------" << endl;

	for (int m = 1; m <= Movie::totalmovie; m++)
		cout << m << "." << db.getmoviename(m) << " | " << db.getmoviertime(m) << "��" << endl;

	int sel1;
	while (true) {
		
		cout << "-------------------------------------------------" << endl;
		cout << "��ȸ�Ͻ� ��ȭ�� �������ּ���" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		cin >> sel1;
		if ((1 <= sel1) && (sel1 <= Movie::totalmovie))
			break;
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "��Ȯ�� �Է����ּ���." << endl;
		}
	}


	int today = db.getbusiday() - 1;
	int countarr[8][8] = { 0 };
	// �ش� ��ȭ�� ���� Ƚ�� �˻�
	for (int day = today - 6 ; day <= today; day++) // day (���÷κ��� 6���� ~ ����) ����
		for (int p = 0; p < 40; p++) // ���α׷� ��ü ���� (40��)
			for (int r = 0; r < 8; r++)
				for (int c = 0; c < 8; c++)
					if (db.prodb[day][p].getmovie() == sel1) // �ش� ��ȭ����
						if (db.prodb[day][p].getseatuser(r, c)) { // 0�ϰ�� false, �� ���� ��� true
							countarr[r][c]++;
						}
	// �˻��� �ڷḦ ���� ū 3�� ����
	cout << "-------------------------------------------------" << endl;
	cout << db.getmoviename(sel1) << " ���� ���� ���Ű� ���� �� �¼��� ������ �����ϴ�." << endl;
	top3_show(countarr);
}

void Analysis::rank_gender(Database& db) {
	int sel1;
	char gen;
	while (true) {
		cout << "-------------------------------------------------" << endl;
		cout << "��ȸ�Ͻ� ������ �������ּ���" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "| 1. ����               | 2. ����               |" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		cin >> sel1;
		if (sel1 == 1) {
			gen = 'M';
			break;
		}
		else if (sel1 == 2) {
			gen = 'F';
			break;
		}
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "��Ȯ�� �Է����ּ���." << endl;
		}
	}
	int today = db.getbusiday() - 1;
	int countarr[8][8] = { 0 };
	// gen ������ ���� Ƚ�� �˻�
	for (int day = today - 6; day <= today; day++) // ���÷κ��� 6����~ ����
		for (int p = 0; p < 40; p++) // ���α׷� ��ü ���� (40��)
			for (int r = 0; r < 8; r++)
				for (int c = 0; c < 8; c++)
					if (db.prodb[day][p].getseatuser(r, c) != 0) // 0�� ��� �ش� �¼��� �̵��
						if (db.getusergender(db.prodb[day][p].getseatuser(r, c)) == gen) // ���� Ȯ�� 
							countarr[r][c]++;
	// �˻��� �ڷḦ ���� ū 3�� ����
	cout << "-------------------------------------------------" << endl;
	if(sel1 == 1)
		cout << "���� ���Բ��� ���� ���� �����Ͻ� �¼��� ������ �����ϴ�." << endl;
	else if (sel1 == 2)
		cout << "���� ���Բ��� ���� ���� �����Ͻ� �¼��� ������ �����ϴ�." << endl;
	top3_show(countarr);
}

void Analysis::rank_theater(Database& db) {
	int sel1;
	while (true) {
		cout << "-------------------------------------------------" << endl;
		cout << "��ȸ�Ͻ� �󿵰� ��ȣ�� �������ּ���" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		cin >> sel1;
		if ((1 <= sel1) && (sel1 <= db.numoftheater))
			break;
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "��Ȯ�� �Է����ּ���." << endl;
		}
	}

	int today = db.getbusiday() - 1;
	int countarr[8][8] = {0};
	// t�󿵰��� ���� Ƚ�� �˻�
	for (int day = today - 6 ; day <= today ; day ++) // day ����
		for (int p = 0; p < 40; p++) // ���α׷� ��ü ���� (40��)
			for (int r = 0; r < 8; r++) 
				for (int c = 0; c < 8; c++)
					if (db.prodb[day][p].gettheater() == sel1) // t �󿵰�����
						if (db.prodb[day][p].getseatuser(r, c)) { // 0�ϰ�� false, �� ���� ��� true
							countarr[r][c]++;
						}
	// �˻��� �ڷḦ ���� ū 3�� ����
	cout << "-------------------------------------------------" << endl;
	cout << sel1 << "�󿵰����� ���� ���Ű� ���� �� �¼��� ������ �����ϴ�." << endl;
	top3_show(countarr);		
}

void Analysis:: top3_show(int countarr[][8]) {
	int arr1[3] = { 0,0,0 }; // 1���� row, column , count
	int arr2[3] = { 0,0,0 }; // 2���� row, column , count
	int arr3[3] = { 0,0,0 }; // 3���� row, column , count
	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++) {
			if (countarr[r][c] > arr1[2]) {
				arr3[0] = arr2[0];
				arr3[1] = arr2[1];
				arr3[2] = arr2[2];
				arr2[0] = arr1[0];
				arr2[1] = arr1[1];
				arr2[2] = arr1[2];
				arr1[0] = r;
				arr1[1] = c;
				arr1[2] = countarr[r][c];
			}
			else if (countarr[r][c] > arr2[2]) {
				arr3[0] = arr1[0];
				arr3[1] = arr1[1];
				arr3[2] = arr1[2];
				arr2[0] = r;
				arr2[1] = c;
				arr2[2] = countarr[r][c];
			}
			else if (countarr[r][c] > arr3[2]) {
				arr3[0] = r;
				arr3[1] = c;
				arr3[2] = countarr[r][c];
			}
		}
	cout << "-------------------------------------------------" << endl;
	if (arr1[2] != 0){
		cout << "1. " << (char)(arr1[0] + 65) << arr1[1] + 1 << " �¼� | " << arr1[2] << "ȸ ���ŵ�" << endl;
		cout << endl;
	}
	if (arr2[2] != 0) {
		cout << "2. " << (char)(arr2[0] + 65) << arr2[1] + 1 << " �¼� | " << arr2[2] << "ȸ ���ŵ�" << endl;
		cout << endl;
	}
	if (arr3[2] != 0) {
		cout << "3. " << (char)(arr3[0] + 65) << arr3[1] + 1 << " �¼� | " << arr3[2] << "ȸ ���ŵ�" << endl;
		cout << "-------------------------------------------------" << endl;
	}	
}

void Analysis::movie_count(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "�� ��ȭ������ �������� ��ȭ�� ������ �����ϴ�." << endl;
	cout << "-------------------------------------------------" << endl;

	for (int m = 1; m <= Movie::totalmovie; m++)
		cout << m << "." << db.getmoviename(m) << " | " << db.getmoviertime(m) << "��" << endl;

	int sel1;
	while (true) {

		cout << "-------------------------------------------------" << endl;
		cout << "��ȸ�Ͻ� ��ȭ�� �������ּ���" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		cin >> sel1;
		if ((1 <= sel1) && (sel1 <= Movie::totalmovie))
			break;
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "��Ȯ�� �Է����ּ���." << endl;
		}
	}
	cout << "-------------------------------------------------" << endl;
	cout << db.getmoviename(sel1) << " �� �����ϼ̽��ϴ�." << endl;
	cout << endl;
	cout << "�¼� ��ġ�� ������ �����ϴ�." << endl;
	showseat();
	cout << "-------------------------------------------------" << endl;
	cout << "�¼� ��ȣ�� �Է����ֽʽÿ� (��:A1) : ";
	string pickedseat;
	int r, c;
	while (true) {
		cin >> pickedseat;
		r = (int)pickedseat[0] - 65;
		c = (int)pickedseat[1] - 49;
		if ((r < 0) || (r > 8) || (c < 0) || (c > 8))
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		else
			break;
		cout << "-------------------------------------------------" << endl;
		cout << "�¼� ��ȣ�� �Է����ֽʽÿ� (��:A1) : ";
	}
	cout << "-------------------------------------------------" << endl;
	cout << pickedseat << "�¼��� �� �����ϼ̽��ϴ�." << endl;
	int today = db.getbusiday() - 1;
	int count = 0;
	// �ش� ��ȭ�� ���� Ƚ�� �˻�
	for (int day = today - 6; day <= today; day++) // day (���÷κ��� 6���� ~ ����) ����
		for (int p = 0; p < 40; p++) // ���α׷� ��ü ���� (40��)
			if (db.prodb[day][p].getmovie() == sel1) // �ش� ��ȭ����
				if (db.prodb[day][p].getseatuser(r, c)) { // 0�ϰ�� false, �� ���� ��� true
					count++;
				}
	cout << "-------------------------------------------------" << endl;
	cout << (char)(r + 65) << c + 1 << " �¼� | " << count << "ȸ ���ŵ�" << endl;
	cout << "-------------------------------------------------" << endl;
}


void Analysis::gender_ratio(Database& db){
	cout << "-------------------------------------------------" << endl;
	cout << "�¼��� ���� ������ ��ȸ�մϴ�." << endl;
	cout << endl;
	cout << "�¼� ��ġ�� ������ �����ϴ�." << endl;
	showseat();
	cout << "-------------------------------------------------" << endl;
	cout << "�¼� ��ȣ�� �Է����ֽʽÿ� (��:A1) : ";
	string pickedseat;
	int r, c;
	while (true) {
		cin >> pickedseat;
		r = (int)pickedseat[0] - 65;
		c = (int)pickedseat[1] - 49;
		if ((r < 0) || (r > 8) || (c < 0) || (c > 8))
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		else
			break;
		cout << "-------------------------------------------------" << endl;
		cout << "�¼� ��ȣ�� �Է����ֽʽÿ� (��:A1) : ";
		}
		cout << "-------------------------------------------------" << endl;
		cout << pickedseat << "�¼��� �� �����ϼ̽��ϴ�." << endl;
	int today = db.getbusiday() - 1;
	int mcount = 0;
	int fcount = 0;
	for (int day = today - 6; day <= today; day++) // day (���÷κ��� 6���� ~ ����) ����
		for (int p = 0; p < 40; p++) // ���α׷� ��ü ���� (40��)
			if (db.prodb[day][p].getseatuser(r, c) != 0) { // 0�� ��� �ش� �¼��� �̵��
				if (db.getusergender(db.prodb[day][p].getseatuser(r, c)) == 'M') // ���� ī��Ʈ 
					mcount++;
				else if (db.getusergender(db.prodb[day][p].getseatuser(r, c)) == 'F') // ���� ī��Ʈ
					fcount++;
			}
	double mratio = (double)mcount / ((double)mcount + (double)fcount);
	cout << "-------------------------------------------------" << endl;
	cout << "| " << (char)(r + 65) << c + 1 << " �¼��� ���� ���� | " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "|   ���� : " << (int) (mratio*100.0)  << "%   |   ���� : " << (int)(100.0*(1.0 - mratio)) << "%   | " << endl;
	cout << "-------------------------------------------------" << endl;
}

void Analysis::time_count(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "�¼� ��ġ�� ������ �����ϴ�." << endl;
	showseat();
	cout << "-------------------------------------------------" << endl;
	cout << "�¼� ��ȣ�� �Է����ֽʽÿ� (��:A1) : ";
	string pickedseat;
	int r, c;
	while (true) {
		cin >> pickedseat;
		r = (int)pickedseat[0] - 65;
		c = (int)pickedseat[1] - 49;
		if ((r < 0) || (r > 8) || (c < 0) || (c > 8))
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		else
			break;
		cout << "-------------------------------------------------" << endl;
		cout << "�¼� ��ȣ�� �Է����ֽʽÿ� (��:A1) : ";
	}
	cout << "-------------------------------------------------" << endl;
	cout << pickedseat << "�¼��� �� �����ϼ̽��ϴ�." << endl;
	int today = db.getbusiday() - 1;
	int stime;
	int daytime = 0; // �ְ� ��ȭ (09�� ~ 17��)
	int nighttime = 0; // �߰� ��ȭ (18�� ~ ���� 01��)
	int jjsy = 0; // ����, �ɾ� ��ȭ (01�� ~ 08��)
	for (int day = today - 6; day <= today; day++) // day (���÷κ��� 6���� ~ ����) ����
		for (int p = 0; p < 40; p++) // ���α׷� ��ü ���� (40��)
			if (db.prodb[day][p].getseatuser(r, c)) { // 0�ϰ�� false, �� ���� ��� true
				stime = db.prodb[day][p].getstime(); // stime�� �ش� ��ȭ ���۽ð�
				if ((stime >= 1) && (stime <= 8))
					jjsy++;
				else if ((stime >= 9) && (stime <= 17))
					daytime++;
				else
					nighttime++;
			}
	cout << "-------------------------------------------------" << endl;
	cout << (char)(r + 65) << c + 1 << " �¼� | " << endl;
	cout << endl;
	cout << endl;
	cout << " �ְ� �ð��� | 09�� ~ 17�� ���� ��ȭ | " << daytime << "ȸ ���ŵ�" << endl;
	cout << endl;
	cout << " �߰� �ð��� | 18�� ~ 01�� ���� ��ȭ | " << nighttime << "ȸ ���ŵ�" << endl;
	cout << endl;
	cout << " �������ɾ� �ð��� | 01�� ~ 08�� ���� ��ȭ | " << jjsy << "ȸ ���ŵ�" << endl;
	cout << "-------------------------------------------------" << endl;
}

void Analysis::showseat() {
	cout << "-------------------------------------------------" << endl;
	cout << endl;
	cout << "--------------------SCREEN--------------------" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < 8; i++) {
		cout << "  ";
		for (int j = 0; j < 8; j++) {
			cout << "|";
			cout << ' ' << (char)(i + 65) << j + 1 << ' ';
		}
		cout << "|" << endl;
		cout << "----------------------------------------------" << endl;
	}
}