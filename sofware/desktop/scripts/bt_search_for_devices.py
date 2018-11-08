from bluetooth import *
import json

print "Search bluetooth devices..."

nearby_devices = discover_devices(lookup_names = True)

#Save data in json file
with open('../assets/data/devices_aviable.json', 'w') as outfile:
    json.dump(nearby_devices, outfile)
    print "json generated"

print "found %d devices" % len(nearby_devices)

for name, addr in nearby_devices:
     print " %s - %s" % (addr, name)
