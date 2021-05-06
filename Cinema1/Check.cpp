#include "Check.h"

#include <iostream>
using namespace std;


void Check::run(Database& db) {
	int i;
	bool flag = false;
	while (!flag) {
		cout << "-------------------------------------------------" << endl;
		cout << "���� Ȯ��/��� �޴��Դϴ�." << endl;
		cout << endl;
		cout << "����� �����Ͻʽÿ�." << endl;
		cout << endl;
		cout << endl;
		cout << "1. ���� Ȯ�� / ���" << endl;
		cout << endl;
		cout << "2. ����Ʈ ��ȸ" << endl;
		cout << endl;
		cout << "3. ���ư���" << endl;
		cout << endl;
		cout << "�޴��� �Է����ֽʽÿ�. : ";
		cin >> i;


		switch (i) { // �޴� ����
		case 1:
			viewncancel(db);
			break;

		case 2:
			pointcheck(db);
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

void Check::viewncancel(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "���� Ȯ���Դϴ�." << endl;
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ȸ������ Ȯ���� ���� ���̵� �Է����ֽʽÿ�." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ID : ";
	string id1;
	cin >> id1;
	cout << "-------------------------------------------------" << endl;
	cout << "��й�ȣ�� �Է����ֽʽÿ�." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "PW : ";
	string pw1;
	cin >> pw1;



	if (db.login(id1, pw1) == 0) {
		cout << "-------------------------------------------------" << endl;
		cout << "�߸��� ID Ȥ�� ��й�ȣ�Դϴ�. �ٽ� Ȯ�����ּ���." << endl;
		cout << endl;
		cout << "ó�� ȭ������ ���ư��ϴ�." << endl;
		cout << "-------------------------------------------------" << endl;
	}
	else {
		int sel_usernum = db.login(id1, pw1);
		string name = db.getusername(sel_usernum);
		cout << "-------------------------------------------------" << endl;
		cout << name << "��, ȯ���մϴ�." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "���� ���ϴ� ��ȭ�� ��ȸ�˴ϴ�." << endl;
		cout << "-------------------------------------------------" << endl;
		int here = 0;
		int darr[40][4];
		int today = db.getbusiday() - 1;
		for (int p = 0; p < 40; p++)
			for (int r = 0; r < 8; r++)
				for (int c = 0; c < 8; c++)
					if (db.prodb[today][p].getseatuser(r, c) == sel_usernum) {
						darr[here][0] = today;
						darr[here][1] = p;
						darr[here][2] = r;
						darr[here][3] = c;
						here++;
					}
		if (here == 0)
			cout << "��ȸ�� ���Ű� �����ϴ�." << endl;
		else {
			for (int i = 0; i < here; i++) {
				cout << i + 1 << "��" << endl;
				cout << db.getmoviename(db.prodb[darr[i][0]][darr[i][1]].getmovie()) << " | �󿵰� " << db.prodb[darr[i][0]][darr[i][1]].gettheater() << endl;
				cout << db.prodb[darr[i][0]][darr[i][1]].getstime() << "�� ���� | " << (char)(darr[i][2] + 65) << (char)(darr[i][3] + 49) << "�¼�" << endl;
				cout << "-------------------------------------------------" << endl;
			}
			cout << "����� ���Ÿ� �������ּ���. ����� ���Ű� �����ø� 0�� �������ּ���." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "�Է� : ";
			int sel1;
			while (true) {
				cin >> sel1;
				if (sel1 == 0) {
					cout << "-------------------------------------------------" << endl;
					cout << "���� ȭ������ ���ư��ϴ�." << endl;
					cout << "-------------------------------------------------" << endl;
					break;
				}
				else if ((sel1 < 0) || (sel1 > here)) {
					cout << "-------------------------------------------------" << endl;
					cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
					cout << endl;
					cout << "����� ���Ÿ� �������ּ���. ����� ���Ű� �����ø� 0�� �������ּ���." << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "�Է� : ";
				}
				else {
					sel1--;
					cout << "-------------------------------------------------" << endl;
					cout << darr[sel1][0] << "�� | " << db.getmoviename(db.prodb[darr[sel1][0]][darr[sel1][1]].getmovie()) << " | �󿵰� " << db.prodb[darr[sel1][0]][darr[sel1][1]].gettheater() << endl;
					cout << db.prodb[darr[sel1][0]][darr[sel1][1]].getstime() << "�� ���� | " << (char)(darr[sel1][2] + 65) << (char)(darr[sel1][3] + 49) << "�¼�" << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "�ش� �¼��� ����Ͻðڽ��ϱ�?" << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "| 1. ��             | 2. �ƴϿ�                 |" << endl;
					cout << "-------------------------------------------------" << endl;
					cout << "�Է� : ";
					int sel2;
					while (true) {
						cin >> sel2;
						if (sel2 == 1) {
							db.prodb[darr[sel1][0]][darr[sel1][1]].bookseat(darr[sel1][2], darr[sel1][3], 0); // �¼� ȯ�� 
							db.setuserpoint(sel_usernum, db.getuserpoint(sel_usernum) - (db.ticket / (100 * db.pointratio))); // ���� ����Ʈ - ��������Ʈ

							cout << "-------------------------------------------------" << endl;
							cout << "���Ű� ��ҵǾ����ϴ�." << endl;
							cout << endl;
							cout << "�ش� ���Ű����� ������ ����Ʈ�� ��ȯ�Ǿ����ϴ�.";
							cout << endl;
							cout << "�̿����ּż� �����մϴ�.";
							cout << "-------------------------------------------------" << endl;
							cout << "ȯ�� �ݾ� : " << db.ticket << "��" << endl;
							cout << endl;
							cout << "�ܿ� ����Ʈ : " << db.getuserpoint(sel_usernum) << "P" << endl;
							cout << "-------------------------------------------------" << endl;
							break;
						}
						else if (sel2 == 2) {
							cout << "-------------------------------------------------" << endl;
							cout << "���� ��Ҹ� ������ ��ҵǾ����ϴ�." << endl;
							cout << endl;
							cout << "�޴� ȭ������ ���ư��ϴ�." << endl;
							cout << "-------------------------------------------------" << endl;
							break;
						}
						else {
							cout << "-------------------------------------------------" << endl;
							cout << "��Ȯ�� �Է����ֽʽÿ�." << endl;
							cout << "-------------------------------------------------" << endl;
							cout << "�Է� : ";
						}
					}
					break;
				}
			}
		}

	}
}


void Check::pointcheck(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "���� Ȯ���Դϴ�." << endl;
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ȸ������ Ȯ���� ���� ���̵� �Է����ֽʽÿ�." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ID : ";
	string id1;
	cin >> id1;
	cout << "-------------------------------------------------" << endl;
	cout << "��й�ȣ�� �Է����ֽʽÿ�." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "PW : ";
	string pw1;
	cin >> pw1;



	if (db.login(id1, pw1) == 0) {
		cout << "-------------------------------------------------" << endl;
		cout << "�߸��� ID Ȥ�� ��й�ȣ�Դϴ�. �ٽ� Ȯ�����ּ���." << endl;
		cout << endl;
		cout << "ó�� ȭ������ ���ư��ϴ�." << endl;
		cout << "-------------------------------------------------" << endl;
	}
	else {
		int sel_usernum = db.login(id1, pw1);
		string name = db.getusername(sel_usernum);
		cout << "-------------------------------------------------" << endl;
		cout << name << "��, ȯ���մϴ�." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�ܿ� ����Ʈ�� " << db.getuserpoint(sel_usernum) << "P �Դϴ�." << endl;
		cout << "-------------------------------------------------" << endl;
	}
}