# Constants
c = 299792458 # [m/s]
g = 9.81 # [m/s^2]
MtoAU = 1 / 149597870691
MtoKM = 1 / 1000
MtoLY = 1 / 9460730472580800
SECtoHOUR = 1 / 3600
SECtoDAYS = 1 / (24 * 3600)

# Trip parameters [EDIT THESE]
vMax = 0.999 * c # Maximum speed [m/s]
D = 4.2 / (MtoLY) # Destination distance [m]
a = 1.2*g # Max sustained acceleration [m/s^2]

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
vAvg = D / tTot
gammaAvg = pow(1 - pow(vAvg,2)/pow(c,2),-0.5)

# Print results
print("-- One-way, 1-D Travel Results --");
print()

print("Trip distance: ", D, " [m]")
print(D * MtoAU, " [AU]")
print(D * MtoLY, " [LY]")
print()

print("Time to arrival: ", tTot, " [s]")
print(tTot * SECtoHOUR, " [hours]")
print(tTot * SECtoDAYS, " [days]")
print()

print("Max speed reached: ", vPeak, " [m/s]")
print(vPeak / c, " [c]")
print()

print("Coast time: ", tCoast, " [s]")
print(tCoast * SECtoHOUR, " [hours]")
print(tCoast * SECtoDAYS, " [days]")
print()

print("Average velocity ", vAvg, " [m/s]")
print(vAvg / c, " [c]")
print("Avg Lorentz factor: ", gammaAvg)
print("Time passed for travelers: ", tTot*SECtoDAYS/gammaAvg, " [days]")
print()
