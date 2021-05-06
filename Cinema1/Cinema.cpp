#include "Cinema.h"
#include "Database.h"
#include "Reservation.h"
#include "Check.h"
#include "Analysis.h"



void Cinema::run() {

	bool flag = false;
	int i;

	Database db;
	
	while (!flag) {
		cout << "-------------------------------------------------" << endl;
		cout << endl;
		cout << "�ȳ��ϼ���, ABC��ȭ���Դϴ�." << endl;
		cout << "�޴��� �����Ͻʽÿ�." << endl;
		cout << endl;
		cout << endl;
		cout << "1. ��ȭ ����" << endl;
		cout << endl;
		cout << "2. ���� Ȯ��/���, ����Ʈ ��ȸ" << endl;
		cout << endl;
		cout << "3. ���� �¼� �м�" << endl;
		cout << endl;
		cout << "4. ����" << endl;
		cout << endl;
		cout << "�޴��� �Է����ֽʽÿ�. : ";
		cin >> i;

		Reservation rv;
		Check ck;
		Analysis ay;

		switch (i) { // �޴� ����
		case 1:
			rv.run(db);
			break;

		case 2:
			ck.run(db);
			break;

		case 3:
			ay.run(db);
			break;

		case 4:
			flag = true;
			break;

		default:
			cout << "-------------------------------------------------" << endl;
			cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
			cout << "-------------------------------------------------" << endl;
			cout << endl;
			break;
		}
	}
}