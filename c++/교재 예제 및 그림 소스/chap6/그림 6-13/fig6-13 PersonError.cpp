class PersonError {
	int money;
public:
	static int getMoney() { return money; } // 컴파일 오류.

	void setMoney(int money) {
		this->money = money; // 정상 코드
	}
};

int main() {
	int n = PersonError::getMoney();

	PersonError errorKim;
	errorKim.setMoney(100);
}