#include "Reservation.h"

#include <iostream>
using namespace std;


void Reservation::run(Database & db) {
	flag1 = false;
	flag2 = false;
	flag3 = false;
	while (!flag1) {
		user_check(db);
	}
	while (!flag2) {
		movie_select(db);
	}
	while (!flag3) {
		seat_select(db);
	}
	payment(db);
}

void Reservation::user_check(Database & db) {
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "ȯ���մϴ�. ������ ��ϵǽ� �����̽Ű���?" << endl;
	cout << endl;
	cout << "�ű� ���Բ����� ȸ�� ����� �ʿ��մϴ�." << endl;
	cout << endl;
	cout << "ȸ�� ����� ���� ABC����Ʈ�� �����غ�����." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "| 1. ȸ���̴�         | 2. ȸ���� �ƴϴ�        |" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "�Է� : ";
	
	int select;
	cin >> select;
	if (select == 1) {
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



		if (db.login(id1, pw1) != 0) { 
			sel_usernum = db.login(id1, pw1);
			string name = db.getusername(sel_usernum);
			cout << "-------------------------------------------------" << endl;
			cout << name << "��, ȯ���մϴ�." << endl;
			cout << "-------------------------------------------------" << endl;
			sel_name = name;
			flag1 = true;
		}
		else {
			cout << "-------------------------------------------------" << endl;
			cout << "�߸��� ID Ȥ�� ��й�ȣ�Դϴ�. �ٽ� Ȯ�����ּ���." << endl;
			cout << endl;
			cout << "ó�� ȭ������ ���ư��ϴ�." << endl;
			cout << "-------------------------------------------------" << endl;
		}
		
	}
	else if (select == 2) {
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�ű� ȸ������� �����մϴ�." << endl;
		cout << endl;
		cout << "ȸ������ ������ �Է����ּ���." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		string name;
		cin.ignore();
		getline(cin, name, '\n');
		char gen;
		while (true) {
			cout << "-------------------------------------------------" << endl;
			cout << name << "ȸ���� ȯ���մϴ�." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "ȸ������ ������ �Է����ּ���." << endl;
			cout << endl;
			cout << "���� ȸ������ M, ����ȸ������ F�� �Է����ּ���." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "�Է� : ";
			cin >> gen;
			if ((gen == 'M') || (gen == 'F'))
				break;
			else{
				cout << "��Ȯ�� �Է����ֽʽÿ�." << endl;
				cout << "���� ȸ������ M, ����ȸ������ F�� �Է����ּ���." << endl;
			}	
		}
		cout << "-------------------------------------------------" << endl;
		cout << "ȸ������ ���̵� �Է����ּ���." << endl;
		string nid;
		while (true) {
			cout << "-------------------------------------------------" << endl;
			cout << "�Է� : ";
			cin >> nid;
			int i = 0;
			while (i < User::totaluser) {
				if (db.getuserid(i) == nid)
					break;
				i++;
			}
			if (i == User::totaluser)
				break;
			else
				cout << "�̹� ��ϵ� ���̵��Դϴ�." << endl;
		}
		cout << "-------------------------------------------------" << endl;
		cout << "ȸ������ ��й�ȣ�� �Է����ּ���." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		string npw;
		cin >> npw;
		cout << "-------------------------------------------------" << endl;
		cout << "ȸ�� ������ Ȯ�����ּ���." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�̸� : " << name << " | ���� : "<< gen <<  endl;
		cout << endl;
		cout << "ID   : " << nid << " | PW   : " << npw << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "������ �����ø� Ȯ����, Ʋ�� ���� �ִٸ� ��Ҹ� �����ּ���." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "| 1. Ȯ��             | 2. ���                 |" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		int sel2;
		while (true) {
			cin >> sel2;
			if (sel2 == 1) {
				db.signup(name, nid, npw, gen);
				sel_name = name;
				sel_usernum = User::totaluser;
				flag1 = true;

				cout << "-------------------------------------------------" << endl;
				cout << name << "ȸ���� ȯ���մϴ�." << endl;
				cout << endl;
				cout << "ABC�ó׸��� �Բ� ���� �ð� �ǽñ� �ٶ��ϴ�." << endl;
				cout << "-------------------------------------------------" << endl;

				
				break;
			}
			else if (sel2 == 2) {
				cout << "-------------------------------------------------" << endl;
				cout << "ȸ�� ����� ����ϼ̽��ϴ�." << endl;
				cout << "���� ȭ������ ���ư��ϴ�." << endl;
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
	}
	else {
		cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << endl;
	}

}

void Reservation::movie_select(Database& db) {
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "��ȭ ���Ÿ� �����մϴ�." << endl;
	cout << "���� ABC�ó׸����� ������ ��ȭ�� ������ �����ϴ�." << endl;
	cout << "-------------------------------------------------" << endl;
	for (int m = 1; m <= Movie::totalmovie; m++)
		cout << m << "." << db.getmoviename(m) << " | " << db.getmoviertime(m) << "��" << endl;
	cout << "-------------------------------------------------" << endl;
	int mov;
	while (true) {
		cout << "-------------------------------------------------" << endl;
		cout << "���Ͻ� ��ȭ�� ��ȣ�� �������ּ���." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		cin >> mov;
		if ((1 <= mov) && (mov <= Movie::totalmovie))
			break;
		else{
			cout << "-------------------------------------------------" << endl;
			cout << "��Ȯ�� �Է����ּ���." << endl;
		}
			
	}
	cout << "-------------------------------------------------" << endl;
	cout << db.getmoviename(mov) << " ��ȭ�� �����ϼ̽��ϴ�." << endl;
	cout << endl;
	cout << "������ �ش� ��ȭ ���α׷��� ������ �����ϴ�." << endl;
	cout << "-------------------------------------------------" << endl;
	int pickedMV = 0;
	int plist[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int bday = db.getbusiday() - 1;
	for (int n = 0; n < 40; n++) {
		if (db.prodb[bday][n].getmovie() == mov) {
			plist[pickedMV] = n;
			cout << pickedMV + 1 << " | " << db.getmoviename(mov) << " | " << db.prodb[bday][n].getstime() << "�� ���� | " << db.prodb[bday][n].gettheater() << "�󿵰�" << endl;
			pickedMV++;
		}
	}
	if (plist[0] == -1) {
		cout << "�ش� ��ȭ�� ���� ������ ���α׷��� �����ϴ�." << endl;
		cout << "-------------------------------------------------" << endl;
	}
	else {
		int select;
		while (true) {
			cout << "-------------------------------------------------" << endl;
			cout << "���Ͻ� ��ȭ�� �������ּ���." << endl;
			cout << "�Է� : ";
			cin >> select;

			if ((select < 1) || plist[select - 1] == -1) {
				cout << "-------------------------------------------------" << endl;
				cout << "��Ȯ�� �Է����ֽʽÿ�." << endl;
			}
			else
				break;
		}
		cout << "-------------------------------------------------" << endl;
		cout << db.getmoviename(mov) << " | " << db.prodb[bday][plist[select - 1]].getstime() << "�� ���� | " << db.prodb[bday][plist[select - 1]].gettheater() << "�󿵰�" << endl;
		cout << "�� �����ϼ̽��ϴ�." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�����ø� Ȯ����, Ʋ�� ���� �ִٸ� ��Ҹ� �����ּ���." << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "| 1. Ȯ��             | 2. ���                 |" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�Է� : ";
		int sel2;
		while (true) {
			cin >> sel2;
			if (sel2 == 1) {
				cout << "-------------------------------------------------" << endl;
				cout << "Ȯ�εǾ����ϴ�." << endl;
				cout << "-------------------------------------------------" << endl;

				sel_movieid = mov;
				sel_programnum = plist[select - 1];
				flag2 = true;
				break;
			}
			else if (sel2 == 2) {
				cout << "-------------------------------------------------" << endl;
				cout << "��ȭ ������ ��ҵǾ����ϴ�." << endl;
				cout << endl;
				cout << "���� ȭ������ ���ư��ϴ�." << endl;
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
	}
	
}

void Reservation::seat_select(Database& db) {
	cout << "�¼��� �����ϰڽ��ϴ�." << endl;
	cout << endl;
	cout << "��ȸ�� �Ÿ��α⿡ ���� ���ŵ� �¼� ��ó ��ĭ�� �̿� �Ұ����մϴ�.";
	cout << endl;
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
			if (db.prodb[(db.getbusiday()-1)][sel_programnum].isseatbooked(i, j))
				cout << " XX ";
			else if ((i != 0) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(i-1, j))
				cout << " -- "; // ���� �Ÿ��α�
			else if ((i != 7) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(i+1, j))
				cout << " -- "; // �Ʒ��� �Ÿ��α�
			else if ((j != 0) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(i, j-1))
				cout << " -- "; // ���� �Ÿ��α�
			else if ((j != 7) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(i, j+1))
				cout << " -- "; // ������ �Ÿ��α�
			else
				cout << ' ' << (char)(i + 65) << j+1 << ' ';
		}
		cout << "|" << endl;
		cout << "----------------------------------------------" << endl;
	}
	cout << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "�¼���ȣ: ��� ������ �¼�" << endl;
	cout << endl;
	cout << "XX : �̹� ����� �¼� / -- : ��ȸ�� �Ÿ��α� ���� �¼�" << endl;
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
		else if (db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r, c))
			cout << "�̹� ���ŵ� �¼��Դϴ�. �ٽ� �Է����ּ���." << endl;
		else if ((r != 0) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r - 1, c))
			cout << "�Ÿ��α� �¼��Դϴ�. �ٽ� �Է����ּ���." << endl;
		else if ((r != 7) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r + 1, c))
			cout << "�Ÿ��α� �¼��Դϴ�. �ٽ� �Է����ּ���." << endl; // �Ʒ��� �Ÿ��α�
		else if ((c != 0) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r, c - 1))
			cout << "�Ÿ��α� �¼��Դϴ�. �ٽ� �Է����ּ���." << endl; // ���� �Ÿ��α�
		else if ((c != 7) && db.prodb[(db.getbusiday() - 1)][sel_programnum].isseatbooked(r, c + 1))
			cout << "�Ÿ��α� �¼��Դϴ�. �ٽ� �Է����ּ���." << endl; // ������ �Ÿ��α�
		else
			break;
		cout << "-------------------------------------------------" << endl;
		cout << "�¼� ��ȣ�� �Է����ֽʽÿ� (��:A1) : ";
	}
	cout << "-------------------------------------------------" << endl;
	cout << pickedseat << " �¼��� �����Ͻðڽ��ϱ�?" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "| 1. Ȯ��             | 2. ���                 |" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "�Է� : ";
	int sel2;
	while (true) {
		cin >> sel2;
		if (sel2 == 1) {
			cout << "-------------------------------------------------" << endl;
			cout << "Ȯ�εǾ����ϴ�." << endl;
			cout << "-------------------------------------------------" << endl;

			sel_row = r;
			sel_col = c;
			flag3 = true;
			break;
		}
		else if (sel2 == 2) {
			cout << "-------------------------------------------------" << endl;
			cout << "�¼� ������ ��ҵǾ����ϴ�." << endl;
			cout << endl;
			cout << "�¼� ���� ȭ������ ���ư��ϴ�." << endl;
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
}

void Reservation::payment(Database& db) {
	cout << "-------------------------------------------------" << endl;
	cout << "������ �����ϰڽ��ϴ�." << endl;
	cout << endl;
	cout << "Ƽ���� 1�Ŵ� " << db.ticket << " ���Դϴ�." << endl;
	cout << endl;
	cout << "������ �������θ� ����˴ϴ�." << endl;
	cout << endl;
	cout << "������ �־��ֽʽÿ�. : " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "�Է� : ";
	int money = 0;
	int inputmoney = 0;
	while (true) {
		cin >> inputmoney;
		money += inputmoney;
		if (money >= db.ticket)
			break;
		else{
			cout << "-------------------------------------------------" << endl;
			cout << "�ݾ��� �����մϴ�. ���� �� �־��ֽʽÿ�. :";
			cout << endl;
			cout << "���� �ܾ� : " << money << "��" <<  endl;
			cout << endl;
			cout << "�Է� : ";
		}
	}
	cout << "-------------------------------------------------" << endl;
	cout << "Ƽ�� 1�� �����մϴ�." << endl;
	cout << endl;
	cout << "����Ʈ�� " << db.ticket / (db.pointratio * 100) << " P �����˴ϴ�." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "������ ����Ͻø� �ʱ� ȭ������ ���ư��ϴ�." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << endl;
	cout << "��ȭ : " << db.getmoviename(sel_movieid);
	cout << endl;
	cout << "�󿵰� : " << db.prodb[(db.getbusiday() - 1)][sel_programnum].gettheater() << " | " << db.prodb[(db.getbusiday() - 1)][sel_programnum].getstime() << "�� ����" << endl;
	cout << endl;
	cout << (char)(sel_row + 65) << (char)(sel_col + 48) << " �¼� | " << db.ticket << "�� | " << " ����Ʈ | " << db.ticket/(db.pointratio*100) << " P ����" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "| 1. Ȯ��             | 2. ���                 |" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "�Է� : ";
	int sel2;
	while (true) {
		cin >> sel2;
		if (sel2 == 1) {
			money -= db.ticket;
			int point = db.ticket / (db.pointratio * 100);
			db.prodb[(db.getbusiday()-1)][sel_programnum].bookseat(sel_row, sel_col, sel_usernum);
			db.setuserpoint(sel_usernum, db.getuserpoint(sel_usernum) + point);
			

			cout << "-------------------------------------------------" << endl;
			cout << "Ƽ���� �����߽��ϴ�." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "��ȭ : " << db.getmoviename(sel_movieid);
			cout << endl;
			cout << "�󿵰� : " << db.prodb[(db.getbusiday() - 1)][sel_programnum].gettheater() << " | " << db.prodb[(db.getbusiday() - 1)][sel_programnum].getstime() << "�� ����" << endl;
			cout << endl;
			cout << (char)(sel_row + 65) << (char)(sel_col + 48) << " �¼� | " << db.ticket << "�� | " << " ����Ʈ | " << point << " P ����" << endl;
			cout << "���� ����Ʈ : " << db.ticket / (db.pointratio * 100) << " P" << endl;
			cout << "-------------------------------------------------" << endl;
			cout << endl;

			if (money > 0) {
				cout << "�Ž����� " << money << "�� ��ȯ�մϴ�." << endl;
				cout << endl;
				cout << "-------------------------------------------------" << endl;
			}

			cout << "�̿����ּż� �����մϴ�." << endl;
			cout << endl;
			cout << "�ʱ� ȭ������ ���ư��ϴ�." << endl;
			cout << "-------------------------------------------------" << endl;

			break;
		}
		else if (sel2 == 2) {
			cout << "-------------------------------------------------" << endl;
			cout << "������ ��ҵǾ����ϴ�." << endl;
			cout << endl;
			cout << "�ʱ� ȭ������ ���ư��ϴ�." << endl;
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
}