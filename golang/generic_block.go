package main

import (
	"bytes"
)

type PrintPacketBlock struct {
}

func (pp *PrintPacketBlock) EvaluateBlock() bool {
	return true
}

func (pp *PrintPacketBlock) ToString() string {
	return "pp"
}

func (pp *PrintPacketBlock) AddCodeBlocks(blk GenericBlock) {
	panic("This is a leaf statement.. No one is supposed to call AddCodeBlocks")
}

func (pp *PrintPacketBlock) CleanUp() {
}

func (pp *PrintPacketBlock) SetJsonDecoder(dec JsonByteDecoderInterface) {
}

func (pp *PrintPacketBlock) SetParentBlock(blk GenericBlock) {
}

func (pp *PrintPacketBlock) GetJsonValueArray(match string) interface{} {
	panic("This is a leaf statement.. No one is supposed to call GetJsonValueArray")
	return nil
}

func NewPrintPacketBlock() *PrintPacketBlock {
	return &PrintPacketBlock{}
}

type IfBlock struct {
	m_lhsExpression GenericExpression
	m_rhsValue      *CompareValue
	m_codeBlocks    *listOfCodeBlocks
	m_parentBlock   GenericBlock
}

func (ifblk *IfBlock) EvaluateBlock() bool {
	lhs_v := ifblk.m_lhsExpression.GetValue()
	GetLogger().Info(lhs_v, " "+ifblk.m_rhsValue.m_comparator.ToString()+" ", ifblk.m_rhsValue.m_rhsValue)

	if ifblk.m_rhsValue.CompareIt(lhs_v) {
		GetLogger().Info(" : Passed")
		for _, eachBlk := range *ifblk.m_codeBlocks {
			GetLogger().Debug("Evaluating block inside If : ", eachBlk.ToString())
			if eachBlk.EvaluateBlock() {
				return true
			}
		}

		if len(*ifblk.m_codeBlocks) < 1 {
			return true
		}
	}
	GetLogger().Info(" : Failed")
	return false
}

func (ifblk *IfBlock) AddCodeBlocks(blk GenericBlock) {
	ifblk.m_codeBlocks.AppendCodeBlock(blk)
}

func (ifblk *IfBlock) ToString() string {
	var if_blk_string bytes.Buffer
	if_blk_string.WriteString("if ")
	if_blk_string.WriteString(ifblk.m_lhsExpression.ToString())
	if_blk_string.WriteString(" " + ifblk.m_rhsValue.m_comparator.ToString())
	if_blk_string.WriteString(" " + ifblk.m_rhsValue.ToString())
	if_blk_string.WriteString(" {\n")
	if_blk_string.WriteString(ifblk.m_codeBlocks.ToString())
	if_blk_string.WriteString("\n}\n")
	return if_blk_string.String()
}

func (ifblk *IfBlock) CleanUp() {
	ifblk.m_lhsExpression.CleanUp()
	for _, eachBlk := range *ifblk.m_codeBlocks {
		eachBlk.CleanUp()
	}
}

func (ifblk *IfBlock) SetParentBlock(blk GenericBlock) {
	ifblk.m_parentBlock = blk
	ifblk.m_lhsExpression.SetParent(ifblk)
	for _, eachBlk := range *ifblk.m_codeBlocks {
		eachBlk.SetParentBlock(ifblk)
	}
}

func (ifblk *IfBlock) SetJsonDecoder(dec JsonByteDecoderInterface) {
	ifblk.m_lhsExpression.SetJsonDecoder(dec)
	for _, eachBlk := range *ifblk.m_codeBlocks {
		eachBlk.SetJsonDecoder(dec)
	}
}

func (ifblk *IfBlock) GetJsonValueArray(match string) interface{} {
	return ifblk.m_parentBlock.GetJsonValueArray(match)
}

func NewIfBlock(lhsExpr GenericExpression, rhs *CompareValue) *IfBlock {
	lhsExpr.SetBlockType(IF_BLOCK)
	return &IfBlock{
		m_lhsExpression: lhsExpr,
		m_rhsValue:      rhs,
		m_codeBlocks:    NewListOfCodeBlock(),
		m_parentBlock:   nil,
	}
}

type ForBlock struct {
	m_lhsIdentifier string
	m_rhsExpression GenericExpression
	m_codeBlocks    *listOfCodeBlocks
	m_parentBlock   GenericBlock
}

func (forblk *ForBlock) EvaluateBlock() bool {

	GetLogger().Debug(" Evaluating For Block with identifier :", forblk.m_lhsIdentifier, " ", forblk.ToString())
	for retVal := forblk.m_rhsExpression.GetValue(); retVal != nil; {

		for _, eachBlk := range *forblk.m_codeBlocks {
			GetLogger().Debug("Evaluating block inside for : ", eachBlk.ToString())
			if eachBlk.EvaluateBlock() {
				return true
			}
		}

		if !forblk.m_rhsExpression.OperatorPlusPlus() {
			break
		}
	}
	GetLogger().Debug("For Block Evaluation failed for identifier: ", forblk.m_lhsIdentifier)
	return false
}

func (forblk *ForBlock) AddCodeBlocks(blk GenericBlock) {
	forblk.m_codeBlocks.AppendCodeBlock(blk)
}

func (forblk *ForBlock) ToString() string {
	var for_blk_string bytes.Buffer
	for_blk_string.WriteString("for ")
	for_blk_string.WriteString(forblk.m_lhsIdentifier)
	for_blk_string.WriteString(" in ")
	for_blk_string.WriteString(forblk.m_rhsExpression.ToString())
	for_blk_string.WriteString(" {\n")
	for_blk_string.WriteString(forblk.m_codeBlocks.ToString())
	for_blk_string.WriteString("\n}\n")
	return for_blk_string.String()
}

func (forblk *ForBlock) CleanUp() {
	forblk.m_rhsExpression.CleanUp()
	for _, eachBlk := range *forblk.m_codeBlocks {
		eachBlk.CleanUp()
	}
}

func (forblk *ForBlock) SetJsonDecoder(dec JsonByteDecoderInterface) {
	forblk.m_rhsExpression.SetJsonDecoder(dec)
	for _, eachBlk := range *forblk.m_codeBlocks {
		eachBlk.SetJsonDecoder(dec)
	}
}

func (forblk *ForBlock) SetParentBlock(blk GenericBlock) {
	forblk.m_parentBlock = blk
	forblk.m_rhsExpression.SetParent(forblk)
	for _, eachBlk := range *forblk.m_codeBlocks {
		eachBlk.SetParentBlock(forblk)
	}
}

func (forblk *ForBlock) GetJsonValueArray(match string) interface{} {
	if match == forblk.m_lhsIdentifier {
		return forblk.m_rhsExpression.GetJsonArray()
	}
	return forblk.m_parentBlock.GetJsonValueArray(match)
}

func NewForBlock(lhs_ident string, rhs GenericExpression) *ForBlock {
	rhs.SetBlockType(FOR_BLOCK)
	return &ForBlock{
		m_lhsIdentifier: lhs_ident,
		m_rhsExpression: rhs,
		m_codeBlocks:    NewListOfCodeBlock(),
		m_parentBlock:   nil,
	}
}
