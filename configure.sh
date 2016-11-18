source /home/pawel/GEANT/geant4.9.6.p02-install/bin/geant4.sh
source /home/pawel/GEANT/geant4.9.6.p02-install/share/Geant4-9.6.2/geant4make/geant4make.sh

export ROOTSYS=/home/pawel/snoing/install/root-5.34.30

source $ROOTSYS/bin/thisroot.sh

export G4WORKDIR=/home/pawel/Code/relative_eff
export G4VIS_USE=1

export LD_LIBRARY_PATH=$CLHEP_BASE_DIR/lib:$G4WORKDIR/tmp/Linux-g++/GeDet:$LD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$CLHEP_BASE_DIR/lib:$G4WORKDIR/tmp/Linux-g++/GeDet:$DYLD_LIBRARY_PATH
