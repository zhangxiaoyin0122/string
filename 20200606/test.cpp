#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class String {
public:
	//��������ʵ��:
	//������: һ�ַ�������Ԫ�صĻ���,���ַ�װ������
	//����Ҫ��ע������ϸ��,�Ϳ���ֱ�ӷ���(�ɶ���д)Ԫ��
	//ʹ�÷�ʽ:������ָ��Ĳ���
	//        1.������ --> ��ȡָ��λ�õ�����
	//        2.λ���ƶ� --> ָ������λ��

	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin() {
		//��һ��Ԫ�ص�λ��
		return _str;
	}
	iterator end() {
		//���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}

	const_iterator begin()const {
		return _str;
	}

	const_iterator end()const {
		return _str + _size;
	}


	//�޲ι��캯��
	String()
		:_str(new char[16])
		, _size(0)
		, _capacity(0)
	{
		_str[_size] = '\0';
	}
	//���캯��
	String(const char* str){
		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size;
	}
	////�������캯��
	//String(const String& str)
	//	:_str(new char[str._capacity+1])
	//	,_size(str._size)
	//	,_capacity(str._capacity)
	//{
	//	//���:��Դ����
	//	strcpy(_str, str._str);
	//}
	//�������캯�����ִ�д��:��������д
	String(const String& str)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		//���ù��캯��:���븴��
		String tmp(str._str);
		Swap(tmp);
	}
	void Swap(String& str) {
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}
	//�������:Ч�ʵ�
	/*void Swap(String& str) {
		//��������
		String tmp = str;
		//��ֵ�����
		str = *this;
		//��ֵ�����
		*this = tmp;
	}*/
	//��ֵ�����
	//String& operator=(const String& str) {
	//	if (this != &str) {		
	//		//���ռ�
	//		char* tmp = new char[str._capacity + 1];
	//		//���ݿ���
	//		strcmp(tmp, str._str);
	//		//ԭ�пռ��ͷ�
	//		delete[] _str;
	//		_str = tmp;
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}
	//��ֵ������ִ�д��
	//���븴��:�������� (��ֵʱ���п�������)
	String& operator=(String str) {
		Swap(str);
		return *this;
	}

	const char* c_str()const {
		return _str;
	}
	//��������
	~String() {
		if (_str) {
			delete[]_str;
			_size = _capacity = 0;
			_str = nullptr;
		}
	}

	char& operator[](size_t pos){
		if (pos < _size)
			return _str[pos];
	}
	const char& operator[](size_t pos)const {
		if (pos < _size)
			return _str[pos];
	}
	size_t size() const{
		return _size;
	}

	void pushback(const char& ch) {
		//�ж��Ƿ���Ҫ����
		if (_size == _capacity) {
			size_t newC = _capacity == 0 ? 1 : 2 * _capacity;
			resver(newC);
		}
		//β�����ַ�
		_str[_size] = ch;
		//����_size
		++_size;
		//��Ҫ���Ǹ���'\0'
		_str[_size] = '\0';
		//insert(_size,ch);
	}
	void resver(size_t n) {
		if (n >  _capacity) {
			//���ռ� : +1 �������'\0'
			char* tmp = new char[n + 1];
			//��������
			strcpy(tmp, _str);
			//�ͷ�ԭ�пռ�
			delete[] _str;
			_str = tmp;
			//��������
			_capacity = n;
		}
	}

	void Append(const char* str) {
		//�������
		int len = strlen(str);
		if (_size + len > _capacity) {
			resver(_size + len);
		}
		//��������
		strcpy(_str + _size, str);
		//����_size
		_size += len;
		//insert(_size,str)
	}

	String& operator+=(const char& ch) {
		pushback(ch);
		return *this;
	}
	String& operator+=(const char* str) {
		Append(str);
		return *this;
	}

	void insert(size_t pos, const char& ch) {
		if (pos > _size)
			return;
		//�ж��Ƿ���Ҫ����  
		if (_size == _capacity) {
			size_t newC = _capacity == 0 ? 1 : 2 * _capacity;
			resver(newC);
		}
		size_t end = _size + 1;
		//Ԫ������ƶ�
		while (end > pos) {
			_str[end] = _str[end - 1];
			--end;
		}
		//����Ԫ��
		_str[pos] = ch;
		//����
		++_size;
	}

	void insert(size_t pos, const char* str) {
		if (pos > _size)
			return;
		//�ж��Ƿ���Ҫ����
		size_t len = strlen(str);
		if (_size + len > _capacity) {
			resver(_size + len);
		}

		size_t end = _size + len;
		while (end > pos+len-1) {
			_str[end] = _str[end - len];
			--end;
		}
		//�����ַ���		
		for (int i = 0; i < len; ++i) {
			_str[pos+i] = str[i];
		}
		//����_size
		_size += len;
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

void test() {
	String str("abcdefgh");

	cout << str.c_str() << endl;

	String::iterator it = str.begin();
	while (it != str.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//��Χfor :�ײ����õ�����ʵ��
	for (const char& ch : str) {
		cout << ch << " ";
	}
	cout << endl;

	//[]����
	for (int i = 0; i < str.size(); ++i) {
		cout << str[i] << " ";
	}
	cout << endl;
}
void test2() {
	String s = " ";
	s.pushback('a');
	s.pushback('b');
	s.pushback('c');
	s.pushback('d');
	s.pushback('e');
	s.pushback('f');
	s.pushback('g');
	cout << s.c_str() << endl;
}
int main() {
	test2();
	return 0;
}