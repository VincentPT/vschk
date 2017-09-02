#include "VehicleDAOMacros.h"
#include "VehicleObjects\StolenVehicleInfo.h"

// This class is exported from the VehicleDAO.dll
class VEHICLEDAO_API StolenVehicleDAO {
public:
	StolenVehicleDAO(void);
	virtual ~StolenVehicleDAO(void);
	
	std::shared_ptr<std::list<StolenVehicleInfo>> findVehicleByRegistrationNumber(const TSTRING&);
	std::shared_ptr<std::list<StolenVehicleInfo>> findVehicle(
		const TSTRING* vehicle_registration,
		const TSTRING* vehicle_make,
		const TSTRING* vehicle_model,
		const TSTRING* owner_name
	);

	static bool connectToDatabase();
	static bool disconnectToDatabase();
};