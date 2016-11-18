export G4WORKDIR=~/geant4
export ROOTSYS=/hepusers/sno+/snocave/libraries/root-5.32.00

export PATH=/hepusers/sno+/snocave/libraries/root-5.32.00/root-5.32.00/bin:$PATH
source $ROOTSYS/bin/thisroot.sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/hepusers/sno+/lib:/hepusers/sno+/lib64:/hepusers/sno+/snocave/libraries/root-5.32.00/lib:/hepusers/sno+/snocave/libraries/zeromq-2.1.11/lib
#export LD_LIBRARY_PATH=~/CLHEP/lib/:$LD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:/hepusers/sno+/lib:/hepusers/sno+/lib64:/hepusers/sno+/snocave/libraries/root-5.32.00/lib:/hepusers/sno+/snocave/libraries/zeromq-2.1.11/lib

