#include <carve/carve.hpp>

namespace shewchuk {
double CARVE_API orient2dfast(const double* pa, const double* pb, const double* pc);
double CARVE_API orient2dexact(const double* pa, const double* pb, const double* pc);
double CARVE_API orient2dslow(const double* pa, const double* pb, const double* pc);
double CARVE_API orient2dadapt(const double* pa, const double* pb, const double* pc,
                     double detsum);
double CARVE_API orient2d(const double* pa, const double* pb, const double* pc);

double CARVE_API orient3dfast(const double* pa, const double* pb, const double* pc,
                    const double* pd);
double CARVE_API orient3dexact(const double* pa, const double* pb, const double* pc,
                     const double* pd);
double CARVE_API orient3dslow(const double* pa, const double* pb, const double* pc,
                    const double* pd);
double CARVE_API orient3dadapt(const double* pa, const double* pb, const double* pc,
                     const double* pd, double permanent);
double CARVE_API orient3d(const double* pa, const double* pb, const double* pc,
                const double* pd);

double CARVE_API incirclefast(const double* pa, const double* pb, const double* pc,
                    const double* pd);
double CARVE_API incircleexact(const double* pa, const double* pb, const double* pc,
                     const double* pd);
double CARVE_API incircleslow(const double* pa, const double* pb, const double* pc,
                    const double* pd);
double CARVE_API incircleadapt(const double* pa, const double* pb, const double* pc,
                     const double* pd, double permanent);
double CARVE_API incircle(const double* pa, const double* pb, const double* pc,
                const double* pd);

double CARVE_API inspherefast(const double* pa, const double* pb, const double* pc,
                    const double* pd, const double* pe);
double CARVE_API insphereexact(const double* pa, const double* pb, const double* pc,
                     const double* pd, const double* pe);
double CARVE_API insphereslow(const double* pa, const double* pb, const double* pc,
                    const double* pd, const double* pe);
double CARVE_API insphereadapt(const double* pa, const double* pb, const double* pc,
                     const double* pd, const double* pe, double permanent);
double CARVE_API insphere(const double* pa, const double* pb, const double* pc,
                const double* pd, const double* pe);
}  // namespace shewchuk
