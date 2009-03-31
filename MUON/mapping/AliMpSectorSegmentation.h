/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

// $Id$
// $MpId: AliMpSectorSegmentation.h,v 1.15 2006/05/24 13:58:21 ivana Exp $

/// \ingroup sector
/// \class AliMpSectorSegmentation
/// \brief A segmentation of the sector.        
///
/// Provides methods related to pads:                                     \n
/// conversion between pad indices, pad location, pad position;
/// finding pad neighbour.
///
/// \author David Guez, Ivana Hrivnacova; IPN Orsay

#ifndef ALI_MP_SECTOR_SEGMENTATION_H
#define ALI_MP_SECTOR_SEGMENTATION_H

#include "AliMpVSegmentation.h"
#include "AliMpPad.h"

#include <TVector2.h>
#include <TExMap.h>

class AliMpSector;
class AliMpMotifPosition;
class AliMpVPadIterator;
class AliMpArea;

class AliMpSectorSegmentation : public AliMpVSegmentation
{
  public:
    AliMpSectorSegmentation(const AliMpSector* sector, Bool_t own = false);
    AliMpSectorSegmentation();
    virtual ~AliMpSectorSegmentation();
    
    // factory methods  
    virtual AliMpVPadIterator* CreateIterator(const AliMpArea& area) const;
    virtual AliMpVPadIterator* CreateIterator() const;

    virtual Int_t GetNeighbours(const AliMpPad& pad, TObjArray& neighbours,
                               Bool_t includeSelf = kFALSE,
                               Bool_t includeVoid = kFALSE) const;
    
    // methods  
    virtual AliMpPad PadByLocation(Int_t manuId, Int_t manuChannel,
                               Bool_t warning = kTRUE) const;
    virtual AliMpPad PadByIndices (Int_t ix, Int_t iy, 
                               Bool_t warning = kTRUE) const;
    virtual AliMpPad PadByPosition(const TVector2& position ,
                               Bool_t warning = kTRUE) const;
    virtual AliMpPad PadByDirection(const TVector2& startPosition, 
                               Double_t distance) const;
 
    virtual Bool_t HasPadByIndices(Int_t ix, Int_t iy) const;
    virtual Bool_t HasPadByLocation(Int_t manuId, Int_t manuChannel) const;
  
    virtual Int_t  MaxPadIndexX() const;
    virtual Int_t  MaxPadIndexY() const;
    virtual Int_t  NofPads() const;

    virtual void   GetAllElectronicCardIDs(TArrayI& ecn) const;
    virtual Int_t  GetNofElectronicCards() const;
    virtual Bool_t HasMotifPosition(Int_t motifPositionID) const;
    virtual AliMpMotifPosition* MotifPosition(Int_t manuId) const;

    virtual AliMp::PlaneType   PlaneType() const;
    virtual AliMp::StationType StationType() const;

    virtual TVector2 Dimensions() const;
    virtual TVector2 Position() const;
  
    virtual void Print(Option_t* opt="") const;
    
    virtual Int_t    Zone(const AliMpPad& pad, Bool_t warning = kTRUE) const;
    virtual TVector2 PadDimensions(Int_t zone, Bool_t warning = kTRUE) const;

    TVector2 GetMinPadDimensions() const;
    Bool_t CircleTest(Int_t ix, Int_t iy) const;
    void   PrintZones() const;
   
    const AliMpSector* GetSector() const;
  
  private:
    /// Not implemented
    AliMpSectorSegmentation(const AliMpSectorSegmentation& right);
    /// Not implemented
    AliMpSectorSegmentation&  operator = (const AliMpSectorSegmentation& right);

    static const Double_t   fgkS1;  ///< the separators used for conversion
    static const Double_t   fgkS2;  ///< of TVector2 to MpPair_t
    
    // methods
    Long_t    GetIndex(const TVector2& vector2) const;
    TVector2  GetVector(Long_t index) const;

    // methods
    void  FillPadDimensionsMap();
    AliMpMotifPosition*  FindMotifPosition(Int_t ix, Int_t iy) const;
    virtual AliMpPad PadByXDirection(const TVector2& startPosition, 
                                     Double_t maxX) const;
    virtual AliMpPad PadByYDirection(const TVector2& startPosition, 
                                     Double_t maxY) const;
 
    // data members   
    const AliMpSector*  fkSector;   ///< Sector
    Bool_t              fIsOwner;   ///< Sector ownership     
    AliMpPad*           fPadBuffer; ///< The pad buffer
    mutable TExMap      fPadDimensionsMap; ///< Map between zone IDs and pad dimensions
    Int_t  fMaxIndexInX;  ///< maximum pad index in x    
    Int_t  fMaxIndexInY;  ///< maximum pad index in y    

  ClassDef(AliMpSectorSegmentation,2)  // Segmentation
};


// inline functions

/// Return the sector
inline const AliMpSector* AliMpSectorSegmentation::GetSector() const
{ return fkSector; }

/// Return station type
inline AliMp::StationType AliMpSectorSegmentation::StationType() const
{ return AliMp::kStation12; }


#endif //ALI_MP_SECTOR_SEGMENTATION_H

