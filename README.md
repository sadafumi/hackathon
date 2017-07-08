# DirectX Library
1.同名のソース・ヘッダーファイルを作成<br>
例：Player.cpp, Player.h<br>

2.ソースファイルにはヘッダーファイルをインクルードして、ヘッダーファイルのはLib/core.cppをインクルードする。<br>
例：Player.cpp -> #include "Player.h", Player.h -> #include "Lib/core.cpp"<br>

3.ヘッダー内にObjectクラスを継承したクラスを作って、InitとUpdate関数をオーバーロードする。<br>
例：<br>
class Player : public Object<br>
{<br>
public:<br>
  void Init(void);<br>
  void Update(void);<br>
private:<br>
  float speed;<br>
}<br>

4.ソースファイルのほうにInitとUpdate関数の中身を書く。<br>
例：<br>
void Player::Init(void)<br>
{<br>
  this->SetTexture(TEXTURE_PLAYER);<br>
}<br>

void Player::Update(void)<br>
{<br>
	if (Input::uKeys['W'])<br>
		this->Move(Vector3(0.0f, -0.5f, 0.0f));<br>
	if (Input::uKeys['S'])<br>
		this->Move(Vector3(0.0f, 0.5f, 0.0f));<br>
	if (Input::uKeys['A'])<br>
		this->UpdateAngle(-1.0f);<br>
	if (Input::uKeys['D'])<br>
		this->UpdateAngle(1.0f);<br>
}<br>

5.3で作ったクラス型のグローバル変数を宣言する。<br>
Player g_player;<br>
