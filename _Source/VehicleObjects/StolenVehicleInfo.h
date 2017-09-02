#pragma once
#include "VehicleOwner.h"
#include <list>
#include <memory>

#define JSON_FILED_REGISTRATION	U("Vehicle_Registration")
#define JSON_FILED_MAKE			U("Vehicle_Make")
#define JSON_FILED_MODEL		U("Vehicle_Model")
#define JSON_FILED_OWNER		U("Vehicle_Owner")

class VEHICLEOBJECTS_API StolenVehicleInfo : public JsonObject
{
	TSTRING _vehicleRegistration;
	TSTRING _vehicleMake;
	TSTRING _vehicleModel;
	VehicleOwnerRef _vehicleOwner;
public:
	StolenVehicleInfo();
	~StolenVehicleInfo();

	const TSTRING& getVehicleRegistration() const;
	void setVehicleRegistration(const TSTRING&);

	const TSTRING& getVehicleMake() const;
	void setVehicleMake(const TSTRING&);

	const TSTRING& getVehicleModel() const;
	void setVehicleModel(const TSTRING&);

	const VehicleOwnerRef& getVehicleOwner() const;
	void setVehicleOwner(const VehicleOwnerRef& vehicleOwner);

	virtual void fromJsonObject(const JSON_T&);
	virtual void toJsonObject(JSON_T& value) const;

	static std::shared_ptr<std::list<StolenVehicleInfo>> parseFromJsonArray(const TSTRING&);
	static TSTRING convertToJsonArray(const std::list<StolenVehicleInfo>&);
};

