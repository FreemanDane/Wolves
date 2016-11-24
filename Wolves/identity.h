#pragma once

enum id_type
{
	id_villager,
	id_wolf,
	id_seer,
	id_guard,
	id_cupit,
	id_witch,
	id_hunter
};

class identity
{
protected:
	id_type t;
	bool protection;
	bool die;
	int lastBeProtected;
	bool lover;
	bool poison;
	bool medicion;
	int life;
public:
	identity(id_type new_id);
	~identity();
	bool getProtection();
	void beProtected();
	void cancelProtected();
	bool beDead();
	int getLastBeProtected();
	void timeGoOn();
	bool getPoison();
	void usePoison();
	bool getMedicion();
	void useMedicion();
	bool getLover();
	int getLife();
	void BeHurted();
	void BeSaved();
};
