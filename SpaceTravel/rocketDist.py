import math

# Constants
c = 299792458 # [m/s]
g = 9.81 # [m/s^2]
MtoAU = 1 / 149597870691
MtoKM = 1 / 1000
MtoLY = 1 / 9460730472580800
SECtoHOUR = 1 / 3600
SECtoDAYS = 1 / (24 * 3600)

# Trip parameters [EDIT THESE]
vMax = 0.1*c # Maximum speed [m/s]
D = 4.2 / (MtoLY) # Destination distance [m]
a = 12 # Max sustained acceleration [m/s^2]

# Calculate trip stats
if D > (vMax*vMax/a): # Plateau @ vMax
	vPeak = vMax
	tAccel = vMax / a
	tCoast = (D - tAccel * vMax) / vMax
else: # No plateau
	vPeak = pow(D * a, 0.5)
	tAccel = vPeak / a
	tCoast = 0

tTot = 2*tAccel + tCoast
vPeak = tAccel * a

# Time dilation
# Lorentz factor gamma = 1/sqrt(1-v^2/c^2)
# Time passed by moving frame = integral(1/gamma(t)dt)
# During coast period, that's just tCoast * sqrt(1-vMax^2/c^2)
# During accel, v(t) = a*t. So we integrate sqrt(1-(at)^2/c^2) dt
# Which I did with integral calculator to get the term1 + term2 eq below

term1 = c*math.asin(a*tAccel/c)/(2*a)
term2 = tAccel*pow(1-pow(a,2)*pow(tAccel,2)/pow(c,2),0.5)/2
tShipAccel = term1 + term2
tShipCoast = tCoast * pow(1-pow(vMax,2)/pow(c,2),0.5)
tShipTotal = tShipCoast + 2*tShipAccel

# Print results
print("-- One-way, 1-D Travel Results --");
print()

print("Trip distance: ", D, " [m]")
print(D * MtoAU, " [AU]")
print(D * MtoLY, " [LY]")
print()

print("Time to arrival (earth frame): ", tTot, " [s]")
print(tTot * SECtoHOUR, " [hours]")
print(tTot * SECtoDAYS, " [days]")
print()

print("Max speed reached: ", vPeak, " [m/s]")
print(vPeak / c, " [c]")
print()

print("Ship accel (dilated): ", tShipAccel * SECtoDAYS, " [days]")
print("Ship coast time (dilated): ", tShipCoast * SECtoDAYS, " [days]")
print("Total time passed for travelers: ", tShipTotal * SECtoDAYS, " [days]")
print()
