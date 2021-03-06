#pragma once

enum id_type
{
	id_villager,
	id_wolf,
	id_seer,
	id_guard,
	id_cupit,
	id_witch,
	id_hunter,
	id_null
};

class identity
{
protected:
	id_type t;
	bool protection;
	bool die;
	int lastBeProtected;
	bool lover;
	bool officer;
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
	void goDie();
	int getLastBeProtected();
	void timeGoOn();
	bool getPoison();
	void usePoison();
	bool getMedicion();
	void useMedicion();
	bool getLover();
	void setLover();
	int getLife();
	void BeHurted();
	void BeSaved();
	bool getOfficer();
	void setOfficer();
	void cancelOfficer();
	id_type getID();
};
