////////////////////////////////////////////////////////////////////////
// Class:       ToFProducer
// Plugin Type: producer (Unknown Unknown)
// File:        ToFProducer_module.cc
//
// Generated at Mon Jan 10 18:44:13 2022 by Varuna Crishan Meddage using cetskelgen
// from  version .
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/View.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "canvas/Persistency/Common/PtrVector.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art_root_io/TFileService.h"
#include "art_root_io/TFileDirectory.h"
#include "canvas/Persistency/Common/FindMany.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "canvas/Persistency/Common/FindOneP.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "lardata/DetectorInfoServices/DetectorPropertiesService.h"
#include "lardata/DetectorInfoServices/DetectorClocksService.h"
#include "lardataalg/DetectorInfo/DetectorPropertiesData.h"

#include "larcore/Geometry/Geometry.h"
#include "nusimdata/SimulationBase/GTruth.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/MCFlux.h"
#include "lardataobj/Simulation/SimChannel.h"
#include "lardataobj/Simulation/AuxDetSimChannel.h"
#include "lardataobj/AnalysisBase/Calorimetry.h"
#include "lardataobj/AnalysisBase/ParticleID.h"
#include "lardataobj/RawData/RawDigit.h"
#include "lardataobj/RawData/BeamInfo.h"
#include "larcoreobj/SummaryData/POTSummary.h"
#include "larsim/MCCheater/BackTrackerService.h"
#include "larsim/MCCheater/ParticleInventoryService.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Slice.h"
#include "lardataobj/RecoBase/Shower.h"
#include "lardataobj/RecoBase/PFParticle.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/RecoBase/EndPoint2D.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"
#include "lardataobj/AnalysisBase/CosmicTag.h"
#include "lardataobj/AnalysisBase/FlashMatch.h"
#include "lardataobj/RecoBase/MCSFitResult.h"
#include "larreco/RecoAlg/TrackMomentumCalculator.h"
#include "larreco/RecoAlg/TrajectoryMCSFitter.h"
#include "lardataobj/RecoBase/MCSFitResult.h"
#include "larreco/RecoAlg/PMAlg/PmaTrack3D.h"
#include "larpandora/LArPandoraInterface/LArPandoraHelper.h"
#include "lardataobj/RecoBase/SpacePoint.h"
#include "lardataobj/RecoBase/OpFlash.h"
#include "lardataobj/AnalysisBase/T0.h"

#include "sbndcode/RecoUtils/RecoUtils.h"
#include "lardataobj/MCBase/MCShower.h"

// sbndcode includes
#include "sbnobj/Common/CRT/CRTHit.hh"
#include "sbnobj/Common/CRT/CRTTrack.hh"
#include "sbndcode/CRT/CRTUtils/CRTT0MatchAlg.h"
#include "sbndcode/CRT/CRTUtils/CRTTrackMatchAlg.h"
#include "sbndcode/CRT/CRTUtils/CRTCommonUtils.h"
#include "sbndcode/CRT/CRTUtils/CRTBackTracker.h"

#include "lardataobj/RecoBase/OpHit.h"

#include "sbnobj/SBND/ToF/ToF.hh"

#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TMinuit.h"
#include "TString.h"
#include "TTimeStamp.h"
#include "TVectorD.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TLine.h"
#include "TAxis.h"
#include "TTimeStamp.h"

#include <vector>
#include <fstream>
#include "TPaveStats.h"
#include <iostream>
#include <string>
#include "math.h"
#include "stdio.h"
#include <iterator>
#include <map>
#include <memory>

using namespace std;

namespace sbnd{
	
class ToFProducer : public art::EDProducer {
public:
  using CRTHit = sbn::crt::CRTHit;
  explicit ToFProducer(fhicl::ParameterSet const& pset);
  
  ToFProducer(ToFProducer const&) = delete;
  ToFProducer(ToFProducer&&) = delete;
  ToFProducer& operator=(ToFProducer const&) = delete;
  ToFProducer& operator=(ToFProducer&&) = delete;

  void beginJob();
  void produce(art::Event& evt) override;
  bool HitCompare(const art::Ptr<CRTHit>& h1, const art::Ptr<CRTHit>& h2);
  

private:
    art::InputTag fOpHitModuleLabel;
    art::InputTag fOpFlashModuleLabel0;
    art::InputTag fOpFlashModuleLabel1;
    art::InputTag fCrtHitModuleLabel;
    art::InputTag fCrtTrackModuleLabel;
    
    double       fCoinWindow;
    double       fOpDelay;
    double       fCRThitThresh;
    double       fFlashPeThresh;
    double       fHitPeThresh;
    double       fBeamLow;
    double       fBeamUp; 
    bool         fLFlash;
    bool         fLFlash_hit;
    bool         fCFlash;
    bool         fCFlash_hit;
    bool         fLhit;
    bool         fChit;

    CRTBackTracker* bt;
    map<int,art::InputTag> fFlashLabels;
    geo::GeometryCore const* fGeometryService;
};

ToFProducer::ToFProducer(fhicl::ParameterSet const& pset): 
EDProducer{pset},
fOpHitModuleLabel(pset.get<art::InputTag>("OpHitModuleLabel")),			
fOpFlashModuleLabel0(pset.get<art::InputTag>("OpFlashModuleLabel0")),
fOpFlashModuleLabel1(pset.get<art::InputTag>("OpFlashModuleLabel1")),
fCrtHitModuleLabel(pset.get<art::InputTag>("CrtHitModuleLabel")),
fCrtTrackModuleLabel(pset.get<art::InputTag>("CrtTrackModuleLabel")),
fCoinWindow(pset.get<double>("CoincidenceWindow")),
fOpDelay(pset.get<double>("OpDelay")), 
fCRThitThresh(pset.get<double>("CRThitThresh")), 
fFlashPeThresh(pset.get<double>("FlashPeThresh")),
fHitPeThresh(pset.get<double>("HitPeThresh")),
fBeamLow(pset.get<double>("BeamLow")),
fBeamUp(pset.get<double>("BeamUp")),
fLFlash(pset.get<bool>("LFlash")),
fLFlash_hit(pset.get<bool>("LFlash_hit")),
fCFlash(pset.get<bool>("CFlash")),
fCFlash_hit(pset.get<bool>("CFlash_hit")),
fLhit(pset.get<bool>("Lhit")),
fChit(pset.get<bool>("Chit")),
bt(new CRTBackTracker(pset.get<fhicl::ParameterSet>("CRTBackTrack")))		
{
 fFlashLabels[0] = fOpFlashModuleLabel0;
 fFlashLabels[1] = fOpFlashModuleLabel1; 
 produces< std::vector<sbnd::ToF::ToF> >();
}

void ToFProducer::beginJob(){
     std::cout<<"job begin..."<<std::endl;
     fGeometryService = lar::providerFrom<geo::Geometry>();
}

void ToFProducer::produce(art::Event& evt)
{
 std::unique_ptr<vector<sbnd::ToF::ToF>> ToF_vec(new vector<sbnd::ToF::ToF>);
 
 art::Handle< std::vector<sbn::crt::CRTTrack> > crtTrackListHandle;
 std::vector< art::Ptr<sbn::crt::CRTTrack> >    crtTrackList;
 if( evt.getByLabel(fCrtTrackModuleLabel,crtTrackListHandle))
     art::fill_ptr_vector(crtTrackList, crtTrackListHandle);
 
 art::FindManyP<sbn::crt::CRTHit> findManyHits(crtTrackListHandle, evt, fCrtTrackModuleLabel); 
 std::vector<std::vector<art::Ptr<CRTHit>>> trackhits;
 
 //================================================================
 
 for(size_t itrk=0; itrk<crtTrackList.size(); itrk++){
     std::vector<art::Ptr<CRTHit>> trkhits = findManyHits.at(itrk);
     std::sort(trkhits.begin(),trkhits.end(),
     [](const art::Ptr<CRTHit>& a, const art::Ptr<CRTHit>& b)->bool
     { 
        return a->ts1_ns < b->ts1_ns; 
     });
     trackhits.push_back(trkhits);
 } // Crt hits coming from are ordered on ascending order by looking into ts1_ns variable
 
 //==================================================================
 
 art::Handle< std::vector<sbn::crt::CRTHit> > crtHitListHandle;
 std::vector< art::Ptr<sbn::crt::CRTHit> >    crtHitList;
 if( evt.getByLabel(fCrtHitModuleLabel,crtHitListHandle))
     art::fill_ptr_vector(crtHitList, crtHitListHandle);
 
 map<int, std::vector<art::Ptr<CRTHit>> > tof_crt_hits;
 map<int, std::vector<art::Ptr<recob::OpHit>> > tof_op_hits;
 map<int, std::vector<art::Ptr<recob::OpFlash>> > tof_op_flashes;
 map<int, std::vector<int>> tof_op_tpc;
 
 for(auto const& crt : crtHitList){	 
     if(!(crt->ts1_ns >= fBeamLow &&  crt->ts1_ns<= fBeamUp)) continue;
     if(crt->peshit < fCRThitThresh) continue;
     
     bool frm_trk=false;
     int index=0;
     
     for(auto const& trkhits: trackhits){
	 for(size_t ihit=0; ihit<trkhits.size(); ihit++){
	     if(HitCompare(trkhits[ihit],crt)){
		frm_trk=true;
		break;
	     }
	  }
	  if(frm_trk) break;
	  index++;
     }
     
     // ================================== Calculatin ToF values using Largest optical hit method =========================
     
     if(fLhit){
        double pehit_max=0;
	bool found_tof = false;
	int ophit_index = -1;
	
	art::Handle< std::vector<recob::OpHit> > opHitListHandle;
        std::vector< art::Ptr<recob::OpHit> >    opHitList;
        if( evt.getByLabel(fOpHitModuleLabel,opHitListHandle) )
            art::fill_ptr_vector(opHitList, opHitListHandle);
	
	for(auto const& hit : opHitList){
	    if(hit->PE()<fHitPeThresh) continue;
	    double thit = hit->PeakTime()*1e3-fOpDelay;
	    
	    if(abs(crt->ts1_ns-thit)<fCoinWindow && hit->PE()>pehit_max){
	       pehit_max = hit->PE();
	       ophit_index = hit.key();
	       found_tof = true;
	    }
	} // loop over optical hit list
	
	if(found_tof){	
	    if(frm_trk){	    
	       tof_crt_hits[index].push_back(crt);
	       tof_op_hits[index].push_back(opHitList[ophit_index]);
	    } // crt hit is coming from crt track
	    
	    else{
		 sbnd::ToF::ToF new_tof;
		 new_tof.tof = crt->ts1_ns - (opHitList[ophit_index]->PeakTime()*1e3-fOpDelay);
		 new_tof.frm_hit = true;
		 new_tof.crt_time = crt->ts1_ns;
		 new_tof.pmt_time = opHitList[ophit_index]->PeakTime()*1e3-fOpDelay;
		 new_tof.crt_tagger = crt->tagger;
		 new_tof.crt_hit_id = crt.key();
		 new_tof.pmt_hit_id = ophit_index;
		 ToF_vec->push_back(new_tof);
	    } // lonely crt hit
	} // found a tof match
	
     } // use Lhit method
     
     // =====================================================================================================================
     
     // ================================== Calculatin ToF values using Closest optical hit method ===========================
     
     if(fChit){
        double ophit_minTOF = DBL_MAX;
	bool found_tof = false;
	int ophit_index = -1;
	
	art::Handle< std::vector<recob::OpHit> > opHitListHandle;
        std::vector< art::Ptr<recob::OpHit> >    opHitList;
        if( evt.getByLabel(fOpHitModuleLabel,opHitListHandle) )
            art::fill_ptr_vector(opHitList, opHitListHandle);
	
	for(auto const& hit : opHitList){
	    if(hit->PE()<fHitPeThresh) continue;
	    double thit = hit->PeakTime()*1e3-fOpDelay;
	    
	    if(abs(crt->ts1_ns-thit)<fCoinWindow && abs(crt->ts1_ns-thit)<ophit_minTOF){
	       ophit_minTOF = abs(crt->ts1_ns-thit);
	       ophit_index = hit.key();
	       found_tof = true;
	    }
	} // loop over optical hit list
	
	if(found_tof){	
	    if(frm_trk){	    
	       tof_crt_hits[index].push_back(crt);
	       tof_op_hits[index].push_back(opHitList[ophit_index]);
	    } // crt hit is coming from crt track
	    
	    else{
		 sbnd::ToF::ToF new_tof;
		 new_tof.tof = crt->ts1_ns - (opHitList[ophit_index]->PeakTime()*1e3-fOpDelay);
		 new_tof.frm_hit = true;
		 new_tof.crt_time = crt->ts1_ns;
		 new_tof.pmt_time = opHitList[ophit_index]->PeakTime()*1e3-fOpDelay;
		 new_tof.crt_tagger = crt->tagger;
		 new_tof.crt_hit_id = crt.key();
		 new_tof.pmt_hit_id = ophit_index;
		 ToF_vec->push_back(new_tof);
	    } // lonely crt hit
	} // found a tof match
	
     } // use Chit method
     
     // =====================================================================================================================
     
     //==================================== Calculation ToF values using Largest optical flash ==============================
     
     if(fLFlash){
        double peflash_max=0;
	bool found_tof = false;
	int opflash_index = -1;
	int flash_tpc = -1;
	
	std::map<int, art::Handle< std::vector<recob::OpFlash> > > flashHandles;
        std::map<int,std::vector< art::Ptr<recob::OpFlash> >> opFlashLists;
	
	for(int i=0; i<2; i++) {
            if( evt.getByLabel(fFlashLabels[i],flashHandles[i]) )
                art::fill_ptr_vector(opFlashLists[i], flashHandles[i]);
        }
	
	for(auto const& flashList : opFlashLists){
	    for(size_t iflash=0; iflash<flashList.second.size(); iflash++){
	        auto const& flash = flashList.second[iflash];
		if(flash->TotalPE()<fFlashPeThresh) continue;
		double tflash = flash->Time()*1e3-fOpDelay;
		if(abs(crt->ts1_ns-tflash)<fCoinWindow && flash->TotalPE()>peflash_max){
		   peflash_max=flash->TotalPE();
		   opflash_index = flash.key();	
		   found_tof = true;
		   flash_tpc = flashList.first;
		} // with in conincidence window and getting the largest flash
	    } // loop over flash list
	} // loop over flash list map
	
	if(found_tof){
	   if(frm_trk){	    
	       tof_crt_hits[index].push_back(crt);
	       tof_op_flashes[index].push_back(opFlashLists[flash_tpc][opflash_index]);
	       tof_op_tpc[index].push_back(flash_tpc);
	    } // crt hit is coming from crt track 
	    
	    else{
	         sbnd::ToF::ToF new_tof;
		 new_tof.tof = crt->ts1_ns - (opFlashLists[flash_tpc][opflash_index]->Time()*1e3-fOpDelay);
		 new_tof.frm_hit = true;
		 new_tof.crt_time = crt->ts1_ns;
		 new_tof.pmt_time = opFlashLists[flash_tpc][opflash_index]->Time()*1e3-fOpDelay;
		 new_tof.crt_tagger = crt->tagger;
		 new_tof.crt_hit_id = crt.key();
		 new_tof.flash_tpc_id = flash_tpc;
		 new_tof.pmt_flash_id = opflash_index;
		 ToF_vec->push_back(new_tof);
	    } // lonely crt hit
	} // found a tof match
	
     } // use LFlash method
     
     //======================================================================================================================
     
     //==================================== Calculation ToF values using Closest optical flash ==============================
     
     if(fCFlash){
        double flash_minTOF = DBL_MAX;
	bool found_tof = false;
	int opflash_index = -1;
	int flash_tpc = -1;
	
	std::map<int, art::Handle< std::vector<recob::OpFlash> > > flashHandles;
        std::map<int,std::vector< art::Ptr<recob::OpFlash> >> opFlashLists;
	
	for(int i=0; i<2; i++) {
            if( evt.getByLabel(fFlashLabels[i],flashHandles[i]) )
                art::fill_ptr_vector(opFlashLists[i], flashHandles[i]);
        }
	
	for(auto const& flashList : opFlashLists){
	    for(size_t iflash=0; iflash<flashList.second.size(); iflash++){
	        auto const& flash = flashList.second[iflash];
		if(flash->TotalPE()<fFlashPeThresh) continue;
		double tflash = flash->Time()*1e3-fOpDelay;
		if(abs(crt->ts1_ns-tflash)<fCoinWindow && abs(crt->ts1_ns-tflash)<flash_minTOF){
		   flash_minTOF= abs(crt->ts1_ns-tflash);
		   opflash_index = flash.key();	
		   found_tof = true;
		   flash_tpc = flashList.first;
		} // with in conincidence window and getting the largest flash
	    } // loop over flash list
	} // loop over flash list map
	
	if(found_tof){
	   if(frm_trk){	    
	       tof_crt_hits[index].push_back(crt);
	       tof_op_flashes[index].push_back(opFlashLists[flash_tpc][opflash_index]);
	       tof_op_tpc[index].push_back(flash_tpc);
	    } // crt hit is coming from crt track 
	    
	    else{
	         sbnd::ToF::ToF new_tof;
		 new_tof.tof = crt->ts1_ns - (opFlashLists[flash_tpc][opflash_index]->Time()*1e3-fOpDelay);
		 new_tof.frm_hit = true;
		 new_tof.crt_time = crt->ts1_ns;
		 new_tof.pmt_time = opFlashLists[flash_tpc][opflash_index]->Time()*1e3-fOpDelay;
		 new_tof.crt_tagger = crt->tagger;
		 new_tof.crt_hit_id = crt.key();
		 new_tof.flash_tpc_id = flash_tpc;
		 new_tof.pmt_flash_id = opflash_index;
		 ToF_vec->push_back(new_tof);
	    } // lonely crt hit
	} // found a tof match
	
     } // use CFlash method
     
     //======================================================================================================================
     
     //=========================Calculation ToF values using Earliest hit of the Largest flash ==============================
     
     if(fLFlash_hit){
        double peflash_max=0;
	bool found_tof = false;
	int opflash_index = -1;
	int flash_tpc = -1;
	int ophit_index = -1;
	
	std::map<int, art::Handle< std::vector<recob::OpFlash> > > flashHandles;
        std::map<int,std::vector< art::Ptr<recob::OpFlash> >> opFlashLists;
	
	for(int i=0; i<2; i++) {
            if( evt.getByLabel(fFlashLabels[i],flashHandles[i]) )
                art::fill_ptr_vector(opFlashLists[i], flashHandles[i]);
        }
	
	art::Handle< std::vector<recob::OpHit> > opHitListHandle;
        std::vector< art::Ptr<recob::OpHit> >    opHitList;
        if( evt.getByLabel(fOpHitModuleLabel,opHitListHandle) )
            art::fill_ptr_vector(opHitList, opHitListHandle);
	
	for(auto const& flashList : opFlashLists){	
	    art::FindManyP<recob::OpHit> findManyOpHits(flashHandles[flashList.first], evt, fFlashLabels[flashList.first]);	
	    for(size_t iflash=0; iflash<flashList.second.size(); iflash++){
	        auto const& flash = flashList.second[iflash];
		if(flash->TotalPE()<fFlashPeThresh) continue;
		double tflash = flash->AbsTime()*1e3-fOpDelay;
		if(abs(crt->ts1_ns-tflash)<fCoinWindow && flash->TotalPE()>peflash_max){
		   peflash_max=flash->TotalPE();
		   opflash_index = flash.key();	
		   found_tof = true;
		   flash_tpc = flashList.first;
		   vector<art::Ptr<recob::OpHit>> hits = findManyOpHits.at(flash.key());
		   double flashMinHitT = DBL_MAX;
		   for(auto const& hit : hits){
		       double tPmt = hit->PeakTime()*1e3-fOpDelay; 
		       if(tPmt < flashMinHitT){
			  flashMinHitT = tPmt;
			  ophit_index =  hit.key();    
		       } // getting the earliest hit
		   } // loop over associated ophits of the flash
		} // with in conincidence window and getting the largest flash
	    } // loop over flash list
	} // loop over flash list map
	
	if(found_tof){
	   if(frm_trk){	    
	       tof_crt_hits[index].push_back(crt);
	       tof_op_flashes[index].push_back(opFlashLists[flash_tpc][opflash_index]);
	       tof_op_tpc[index].push_back(flash_tpc);
	       tof_op_hits[index].push_back(opHitList[ophit_index]);
	    } // crt hit is coming from crt track 
	    
	    else{
	         sbnd::ToF::ToF new_tof;
		 new_tof.tof = crt->ts1_ns - (opHitList[ophit_index]->PeakTime()*1e3-fOpDelay);
		 new_tof.frm_hit = true;
		 new_tof.crt_time = crt->ts1_ns;
		 new_tof.pmt_time = opHitList[ophit_index]->PeakTime()*1e3-fOpDelay;
		 new_tof.crt_tagger = crt->tagger;
		 new_tof.crt_hit_id = crt.key();
		 new_tof.flash_tpc_id = flash_tpc;
		 new_tof.pmt_flash_id = opflash_index;
		 new_tof.pmt_hit_id = ophit_index;
		 ToF_vec->push_back(new_tof);
	    } // lonely crt hit
	} // found a tof match
	
     } // use earliest optical hit of the largest flash
     
     //======================================================================================================================
     
     //=========================Calculation ToF values using Earliest hit of the Closest flash ==============================
     
     if(fCFlash_hit){
        double flash_minTOF = DBL_MAX;
	bool found_tof = false;
	int opflash_index = -1;
	int flash_tpc = -1;
	int ophit_index = -1;
	
	std::map<int, art::Handle< std::vector<recob::OpFlash> > > flashHandles;
        std::map<int,std::vector< art::Ptr<recob::OpFlash> >> opFlashLists;
	
	for(int i=0; i<2; i++) {
            if( evt.getByLabel(fFlashLabels[i],flashHandles[i]) )
                art::fill_ptr_vector(opFlashLists[i], flashHandles[i]);
        }
	
	art::Handle< std::vector<recob::OpHit> > opHitListHandle;
        std::vector< art::Ptr<recob::OpHit> >    opHitList;
        if( evt.getByLabel(fOpHitModuleLabel,opHitListHandle) )
            art::fill_ptr_vector(opHitList, opHitListHandle);
	
	for(auto const& flashList : opFlashLists){	
	    art::FindManyP<recob::OpHit> findManyOpHits(flashHandles[flashList.first], evt, fFlashLabels[flashList.first]);	
	    for(size_t iflash=0; iflash<flashList.second.size(); iflash++){
	        auto const& flash = flashList.second[iflash];
		if(flash->TotalPE()<fFlashPeThresh) continue;
		double tflash = flash->Time()*1e3-fOpDelay;
		if(abs(crt->ts1_ns-tflash)<fCoinWindow && abs(crt->ts1_ns-tflash)<flash_minTOF){
		   flash_minTOF= abs(crt->ts1_ns-tflash);
		   opflash_index = flash.key();	
		   found_tof = true;
		   flash_tpc = flashList.first;
		   vector<art::Ptr<recob::OpHit>> hits = findManyOpHits.at(flash.key());
		   double flashMinHitT = DBL_MAX;
		   for(auto const& hit : hits){
		       double tPmt = hit->PeakTime()*1e3-fOpDelay; 
		       if(tPmt < flashMinHitT){
			  flashMinHitT = tPmt;
			  ophit_index =  hit.key();    
		       } // getting the earliest hit
		   } // loop over associated ophits of the flash
		} // with in conincidence window and getting the largest flash
	    } // loop over flash list
	} // loop over flash list map
	
	if(found_tof){
	   if(frm_trk){	    
	       tof_crt_hits[index].push_back(crt);
	       tof_op_flashes[index].push_back(opFlashLists[flash_tpc][opflash_index]);
	       tof_op_tpc[index].push_back(flash_tpc);
	       tof_op_hits[index].push_back(opHitList[ophit_index]);
	    } // crt hit is coming from crt track 
	    
	    else{
	         sbnd::ToF::ToF new_tof;
		 new_tof.tof = crt->ts1_ns - (opHitList[ophit_index]->PeakTime()*1e3-fOpDelay);
		 new_tof.frm_hit = true;
		 new_tof.crt_time = crt->ts1_ns;
		 new_tof.pmt_time = opHitList[ophit_index]->PeakTime()*1e3-fOpDelay;
		 new_tof.crt_tagger = crt->tagger;
		 new_tof.crt_hit_id = crt.key();
		 new_tof.flash_tpc_id = flash_tpc;
		 new_tof.pmt_flash_id = opflash_index;
		 new_tof.pmt_hit_id = ophit_index;
		 ToF_vec->push_back(new_tof);
	    } // lonely crt hit
	} // found a tof match
	
     } // use earliest optical hit of the closest flash
     
     //======================================================================================================================
     
 } // loop over crt hit list
 
 //=================================== Calculation ToF values using Largest optical flash ===================================
 
 if(fLhit){
    if(!tof_crt_hits.empty()){
       for (auto& ele: tof_crt_hits){
	    double min_time = DBL_MAX; 
	    int all_index = 0;
	    int min_index = 0;  
            for (auto const& hit:  ele.second){
		  if(hit->ts1_ns < min_time){ 
	            min_time = hit->ts1_ns;
		    min_index = all_index;
		 }
		 all_index++;
	    } 
	    
	    sbnd::ToF::ToF new_tof;
	    new_tof.tof = trackhits[ele.first].front()->ts1_ns - (tof_op_hits[ele.first][min_index]->PeakTime()*1e3-fOpDelay);
	    new_tof.crt_time = trackhits[ele.first].front()->ts1_ns;
	    new_tof.pmt_time = tof_op_hits[ele.first][min_index]->PeakTime()*1e3-fOpDelay;
	    new_tof.crt_tagger = trackhits[ele.first].front()->tagger;
	    new_tof.frm_trk = true;
	    new_tof.crt_trk_id = ele.first;
	    new_tof.pmt_hit_id = tof_op_hits[ele.first][min_index].key();
	    ToF_vec->push_back(new_tof);
       }
    }
 }
 
 //============================================================================================================================= 
 
 // ================================== Calculatin ToF values using Closest optical hit method ==================================
 
 if(fChit){
    if(!tof_crt_hits.empty()){
       for (auto& ele: tof_crt_hits){
	    double min_time = DBL_MAX; 
	    int all_index = 0;
	    int min_index = 0;  
            for (auto const& hit:  ele.second){
		  if(hit->ts1_ns < min_time){ 
	            min_time = hit->ts1_ns;
		    min_index = all_index;
		 }
		 all_index++;
	    } 
	    
	    sbnd::ToF::ToF new_tof;
	    new_tof.tof = trackhits[ele.first].front()->ts1_ns - (tof_op_hits[ele.first][min_index]->PeakTime()*1e3-fOpDelay);
	    new_tof.crt_time = trackhits[ele.first].front()->ts1_ns;
	    new_tof.pmt_time = tof_op_hits[ele.first][min_index]->PeakTime()*1e3-fOpDelay;
	    new_tof.crt_tagger = trackhits[ele.first].front()->tagger;
	    new_tof.frm_trk = true;
	    new_tof.crt_trk_id = ele.first;
	    new_tof.pmt_hit_id = tof_op_hits[ele.first][min_index].key();
	    ToF_vec->push_back(new_tof);
       }
    }
 }
 
 // ============================================================================================================================
 
 //=================================== Calculatin ToF values using Largest optical flash method ==================================
 
 if(fLFlash){
    if(!tof_crt_hits.empty()){
       for (auto& ele: tof_crt_hits){
            double min_time = DBL_MAX; 
	    int all_index = 0;
	    int min_index = 0;  
	    for (auto const& hit:  ele.second){
		  if(hit->ts1_ns < min_time){ 
	            min_time = hit->ts1_ns;
		    min_index = all_index;
		 }
		 all_index++;
	    }
	    
	    sbnd::ToF::ToF new_tof;
	    new_tof.tof = trackhits[ele.first].front()->ts1_ns - (tof_op_flashes[ele.first][min_index]->Time()*1e3-fOpDelay); 
	    new_tof.crt_time = trackhits[ele.first].front()->ts1_ns;
	    new_tof.pmt_time = tof_op_flashes[ele.first][min_index]->Time()*1e3-fOpDelay;
	    new_tof.crt_tagger = trackhits[ele.first].front()->tagger;
	    new_tof.frm_trk = true;
	    new_tof.crt_trk_id = ele.first;
	    new_tof.flash_tpc_id = tof_op_tpc[ele.first][min_index];
	    new_tof.pmt_flash_id = tof_op_flashes[ele.first][min_index].key();
	    ToF_vec->push_back(new_tof);
       }
    }
 }
 
 //=============================================================================================================================
 
 //=================================== Calculatin ToF values using Closest optical flash method ================================
 
 if(fCFlash){
    if(!tof_crt_hits.empty()){
       for (auto& ele: tof_crt_hits){
            double min_time = DBL_MAX; 
	    int all_index = 0;
	    int min_index = 0;  
	    for (auto const& hit:  ele.second){
		  if(hit->ts1_ns < min_time){ 
	            min_time = hit->ts1_ns;
		    min_index = all_index;
		 }
		 all_index++;
	    }
	    
	    sbnd::ToF::ToF new_tof;
	    new_tof.tof = trackhits[ele.first].front()->ts1_ns - (tof_op_flashes[ele.first][min_index]->Time()*1e3-fOpDelay); 
	    new_tof.crt_time = trackhits[ele.first].front()->ts1_ns;
	    new_tof.pmt_time = tof_op_flashes[ele.first][min_index]->Time()*1e3-fOpDelay;
	    new_tof.crt_tagger = trackhits[ele.first].front()->tagger;
	    new_tof.frm_trk = true;
	    new_tof.crt_trk_id = ele.first;
	    new_tof.flash_tpc_id = tof_op_tpc[ele.first][min_index];
	    new_tof.pmt_flash_id = tof_op_flashes[ele.first][min_index].key();
	    ToF_vec->push_back(new_tof);
       }
    }
 }
 
 //=============================================================================================================================
 
 //=========================Calculation ToF values using Earliest hit of the Largest flash =====================================
 
 if(fLFlash_hit){
    if(!tof_crt_hits.empty()){
       for (auto& ele: tof_crt_hits){
            double min_time = DBL_MAX; 
	    int all_index = 0;
	    int min_index = 0;  
	    for (auto const& hit:  ele.second){
		  if(hit->ts1_ns < min_time){ 
	            min_time = hit->ts1_ns;
		    min_index = all_index;
		 }
		 all_index++;
	    }
	    
	    sbnd::ToF::ToF new_tof;
	    new_tof.tof = trackhits[ele.first].front()->ts1_ns - (tof_op_hits[ele.first][min_index]->PeakTime()*1e3-fOpDelay); 
	    new_tof.crt_time = trackhits[ele.first].front()->ts1_ns;
	    new_tof.pmt_time = tof_op_hits[ele.first][min_index]->PeakTime()*1e3-fOpDelay;
	    new_tof.crt_tagger = trackhits[ele.first].front()->tagger;
	    new_tof.frm_trk = true;
	    new_tof.crt_trk_id = ele.first;
	    new_tof.flash_tpc_id = tof_op_tpc[ele.first][min_index];
	    new_tof.pmt_flash_id = tof_op_flashes[ele.first][min_index].key();
	    new_tof.pmt_hit_id = tof_op_hits[ele.first][min_index].key();
	    ToF_vec->push_back(new_tof);
       }
    }
 } 
 
 //============================================================================================================================
 
 //=========================Calculation ToF values using Earliest hit of the Closest flash ====================================
 
 if(fCFlash_hit){
    if(!tof_crt_hits.empty()){
       for (auto& ele: tof_crt_hits){
            double min_time = DBL_MAX; 
	    int all_index = 0;
	    int min_index = 0;  
	    for (auto const& hit:  ele.second){
		  if(hit->ts1_ns < min_time){ 
	            min_time = hit->ts1_ns;
		    min_index = all_index;
		 }
		 all_index++;
	    }
	    
	    sbnd::ToF::ToF new_tof;
	    new_tof.tof = trackhits[ele.first].front()->ts1_ns - (tof_op_hits[ele.first][min_index]->PeakTime()*1e3-fOpDelay); 
	    new_tof.crt_time = trackhits[ele.first].front()->ts1_ns;
	    new_tof.pmt_time = tof_op_hits[ele.first][min_index]->PeakTime()*1e3-fOpDelay;
	    new_tof.crt_tagger = trackhits[ele.first].front()->tagger;
	    new_tof.frm_trk = true;
	    new_tof.crt_trk_id = ele.first;
	    new_tof.flash_tpc_id = tof_op_tpc[ele.first][min_index];
	    new_tof.pmt_flash_id = tof_op_flashes[ele.first][min_index].key();
	    new_tof.pmt_hit_id = tof_op_hits[ele.first][min_index].key();
	    ToF_vec->push_back(new_tof);
       }
    }
 } 
 //============================================================================================================================
 
 evt.put(std::move(ToF_vec));
}

bool ToFProducer::HitCompare(const art::Ptr<CRTHit>& hit1, const art::Ptr<CRTHit>& hit2) {

      if(hit1->ts1_ns != hit2->ts1_ns) return false;
      if(hit1->plane  != hit2->plane) return false;
      if(hit1->x_pos  != hit2->x_pos) return false;
      if(hit1->y_pos  != hit2->y_pos) return false;
      if(hit1->z_pos  != hit2->z_pos) return false;
      if(hit1->x_err  != hit2->x_err) return false;
      if(hit1->y_err  != hit2->y_err) return false;
      if(hit1->z_err  != hit2->z_err) return false;
      if(hit1->tagger != hit2->tagger) return false;
      return true;
}

DEFINE_ART_MODULE(ToFProducer)
}
